from ct.src.engine import SDL_RenderCopy
from ct.src.guild import Guild
from ct.src.image import *
from ct.src.constants import UnitName, ImageName, ItemType, UnitType, TweenHigherLevelType, BuildingName, BuildingType, UnitAIState, AIAbilityCondition, ItemName, UnitAnimState, AbilityName, TextAlignment, TextWordWrap, FontStyle, Faction, TweenType, HandleType
from ct.src.utils import MoveOptions, get_guild_color, SDL_Point, SDL_Rect, create_rect, get_faction_color, create_color, create_point, get_move_grid_size_dims, manhattan_distance, tile_point_to_world_point, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.image import Image
from ct.src.ct_array import find_and_remove_handle
from ct.src.base_types import Array, N, T, array_capacity, addr, deref, cast, char, array_get_buffer, mod, Uint32
from ct.src.unit_sprite import UnitSprite
from ct.src.tween import TweenXY, TweenCallback
from ct.src.text import TextLG
from ct.src.ability import Ability
from ct.src.stats import Stats
from ct.src.shared_item import SharedItem
from ct.src.inventory import Inventory
from ct.src.shared_ability import SharedAbility
from ct.src.ai import AIAbility
from ct.src.ui_sprite import UISprite
# weak imports
from ct.src.game import Game
from ct.src.map import Map


class Unit:
    def __init__(self):
        self.unit_type: UnitType = None
        self.unit_name: UnitName = None
        self.faction: Faction = None
        self.stats: Stats = None
        self.sprite: UnitSprite = None
        self.map_handle: int = None
        self.battle_map_handle: int = None
        self.tile_point_hit_box: SDL_Rect = None
        self.job_abilities: Array[SharedAbility] = Array[SharedAbility](10)
        self.abilities: Array[SharedAbility] = Array[SharedAbility](30)
        self.default_attack_ability: SharedAbility = None
        self.item_drops: Array[SharedItem] = Array[SharedItem](5)
        self.ai_abilities: Array[AIAbility] = Array[AIAbility](30)
        self.inventory: Inventory = None
        self.display_name: Array[char] = Array[char](100)
        self.display_name_text: TextLG = None
        self.guild_display_name: Array[char] = Array[char](100)
        self.guild_display_name_text: TextLG = None
        self.guild_icon: UISprite = None
        self.merchant_shop_background: UISprite = None
        self.merchant_shop_text: TextLG = None
        self.guild_handle: int = None
        self.available_stat_points: int = None
        self.available_skill_points: int = None
        self.aggro_towards_unit_handle: int = None
        self.last_move_calc_time: Uint32 = None
        self.last_failed_path_time: Uint32 = None
        self.last_try_merchant_buy_time: Uint32 = None
        self.last_attack_time: Uint32 = None
        self.last_sit_heal_time: Uint32 = None
        self.last_non_guild_merchant_restock_time: Uint32 = None
        self.neutral_can_try_buy_again_time: Uint32 = None
        self.path_could_not_be_found: bool = None
        self.next_random_move_time: Uint32 = None
        self.death_time: Uint32 = None
        self.respawn_time: Uint32 = None
        self.aggro_nearest_unit: bool = None
        self.attacked_by_guild_handle: int = None
        self.unit_handle_buying_from_merchant: int = None
        self.ai_state: UnitAIState = None
        self.is_sitting: bool = None
        self.inside_building: bool = None
        self.handle: int = None
        self.in_use_in_pool: bool = None

    def init(self, game: Game, handle: int):
        self.handle = handle
        self.in_use_in_pool = False

        # init values
        self.inventory.init()
        self.map_handle = -1
        self.aggro_towards_unit_handle = -1
        self.attacked_by_guild_handle = -1
        self.unit_handle_buying_from_merchant = -1
        self.ai_state = UnitAIState.Battle
        self.ai_abilities.size = array_capacity(self.ai_abilities)
        for ai_ability in self.ai_abilities:
            ai_ability.clear()

        # init ui values
        text_dst = create_point(0, 0)
        text_color = create_color(255, 255, 255, 255)
        text_outline_color = create_color(0, 0, 0, 255)
        self.display_name_text.text_set(game, array_get_buffer(self.display_name), text_dst, FontStyle.Bold, TextAlignment.Left,
                                        TextWordWrap.NoWrap, 500, 16, text_color, 1, text_outline_color, False)
        self.display_name_text.render_dst.is_camera_rendered = True
        self.guild_display_name_text.text_set(game, array_get_buffer(self.guild_display_name), text_dst, FontStyle.Bold, TextAlignment.Left,
                                              TextWordWrap.NoWrap, 500, 16, text_color, 1, text_outline_color, False)
        self.guild_display_name_text.render_dst.is_camera_rendered = True
        self.merchant_shop_background.render_dst.is_camera_rendered = True
        self.merchant_shop_background.anim_speed = 100
        src = create_rect(0, 512, 80, 20)
        self.merchant_shop_background.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, src)
        text_color = create_color(0, 0, 0, 255)
        self.merchant_shop_text.text_set(game, "Slyme cards", text_dst, FontStyle.Bold, TextAlignment.Left,
                                         TextWordWrap.NoWrap, 500, 10, text_color, 0, text_outline_color, False)
        self.merchant_shop_text.render_dst.is_camera_rendered = True
        # default guild icon even if it isn't rendered (enemies don't render a guild icon)
        self.guild_icon.render_dst.is_camera_rendered = True
        self.guild_icon.anim_speed = 100
        src = create_rect(0, 60, 16, 16)
        self.guild_icon.shared_srcs = game.sprite_db.find(
            game, ImageName.Items, src)

    def update(self, game: Game):
        # update ai
        if self.unit_type == UnitType.TownsPerson:
            self.update_towns_person_ai(game)
        elif self.is_merchant():
            self.update_merchant_ai(game)
        else:
            self.update_ai(game)

        # update values
        self.sprite.update(game, self.map_handle == 0)
        guild = game.world.guilds.at(self.guild_handle)

        # ui
        self.guild_icon.render_dst.dst = self.sprite.render_dst.dst
        self.guild_icon.render_dst.dst.x -= 14
        if self.ai_state == UnitAIState.MerchantSelling:
            self.guild_icon.render_dst.dst.y += 42
        else:
            self.guild_icon.render_dst.dst.y -= 18
        self.guild_icon.update(game)
        if guild.is_anonymous:
            self.display_name_text.render_dst.dst = self.sprite.render_dst.dst
            self.display_name_text.render_dst.dst.x -= 5
            if self.ai_state == UnitAIState.MerchantSelling:
                self.display_name_text.render_dst.dst.y += 42
            else:
                self.display_name_text.render_dst.dst.y -= 13
        else:
            self.display_name_text.render_dst.dst = self.guild_icon.render_dst.dst
            self.display_name_text.render_dst.dst.x += 18
            self.display_name_text.render_dst.dst.y -= 2
        self.display_name_text.text_update(game)
        self.guild_display_name_text.render_dst.dst = self.display_name_text.render_dst.dst
        self.guild_display_name_text.render_dst.dst.y += 10
        self.guild_display_name_text.text_update(game)

        # merchant ui (should this be in a separate function just for merchants?)
        # leaving it like this now for simplicity.
        self.merchant_shop_background.render_dst.dst = self.sprite.render_dst.dst
        self.merchant_shop_background.render_dst.dst.x -= 30
        self.merchant_shop_background.render_dst.dst.y -= 20
        self.merchant_shop_text.render_dst.dst = self.merchant_shop_background.render_dst.dst
        self.merchant_shop_text.render_dst.dst.x += 19
        self.merchant_shop_text.render_dst.dst.y += 5
        self.merchant_shop_background.update(game)
        self.merchant_shop_text.text_update(game)

    def draw(self, game: Game):
        if self.inside_building:
            return
        self.sprite.draw(game)
        self.display_name_text.text_draw(game)
        guild = game.world.guilds.at(self.guild_handle)
        if self.faction != Faction.Enemy:
            if not(guild.is_anonymous):
                self.guild_icon.draw(game)
                self.guild_display_name_text.text_draw(game)
        if self.is_merchant() and self.ai_state == UnitAIState.MerchantSelling:
            self.merchant_shop_background.draw(game)
            self.merchant_shop_text.text_draw(game)

    def draw_idle_at(self, game: Game, unscaled_dst: SDL_Rect):
        # for when ui wants to draw the unit somewhere and maybe the units gear later
        idle_src_0 = self.sprite.idle_down.at(0)
        unscaled_dst.w = idle_src_0.w
        unscaled_dst.h = idle_src_0.h
        set_scaled_rect(unscaled_dst, game.engine.scale)
        SDL_RenderCopy(game.engine.renderer, self.sprite.image.texture,
                       idle_src_0, unscaled_dst)

    def join_guild(self, game: Game, guild: Guild):
        guild = game.world.guilds.at(guild.handle)
        if self.is_merchant():
            guild.merchant_handles.push_value(self.handle)
        else:
            guild.unit_handles.push_value(self.handle)
        self.guild_handle = guild.handle

        # set ui values
        self.guild_display_name.string_set_literal("<")
        self.guild_display_name.string_cat(guild.display_name)
        self.guild_display_name.string_cat_literal(">")

        self.guild_display_name_text.str.string_set(self.guild_display_name)

        self.guild_icon.render_dst.is_camera_rendered = True
        self.guild_icon.anim_speed = 100
        icon_w = 16
        src = create_rect(icon_w * self.guild_handle, 60, 16, 16)
        self.guild_icon.shared_srcs = game.sprite_db.find(
            game, ImageName.Items, src)

    def join_map(self, game: Game, map: Map):
        # no longer attacking a unit
        self.aggro_towards_unit_handle = -1
        if self.map_handle != -1:
            current_map = game.world.maps.at(self.map_handle)
            find_and_remove_handle(current_map.unit_handles, self.handle)
            # reset anyone who is targetting this unit
            for i in range(current_map.unit_handles.size):
                unit_handle = current_map.unit_handles[i]
                unit = game.world.units.at(unit_handle)
                if unit.aggro_towards_unit_handle == self.handle:
                    unit.aggro_towards_unit_handle = -1
            # save the old map handle so the unit can return after selling if necessary
            # if teleported to a new battle map, it doens't matter as when the unit
            # finally teleports to a town map it will be reset here.
            if current_map.handle != 0 and not(current_map.is_town_map):
                self.battle_map_handle = current_map.handle

        # join new map
        self.map_handle = map.handle
        map.unit_handles.push_value(self.handle)

    def is_merchant(self) -> bool:
        return self.unit_name == UnitName.Merchant

    def update_ai(self, game: Game):
        if self.is_merchant():
            print(
                "Unit.update_ai. Unit is a merchant. This ai is only for non-merchants.")
            exit(1)

        if self.ai_state == UnitAIState.Battle:
            # if dead check for respawn time
            if self.stats.hp.value_is_at_min():
                death_time_diff = cast(
                    game.engine.current_time - self.death_time, "Uint32")
                if death_time_diff > self.respawn_time:
                    self.is_sitting = False
                    # respawned, set hp to max for next update
                    self.stats.hp.set_to_max()
                    # reset any anims (death, sit) to idle
                    self.sprite.play_animation(game, UnitAnimState.Idle)
                    # delay the newly respawned unit from random moving for a short time
                    rand_move_delay = cast(400, "Uint32")
                    self.next_random_move_time = game.engine.current_time + rand_move_delay
                    # set respawn point
                    self.set_random_spawn_point(game)
                return
            # if sitting return early don't look for a new target
            sit_pct = 0.4
            if not(self.is_sitting) and self.faction != Faction.Enemy and self.stats.hp.value_pct_of_max() <= sit_pct and self.aggro_towards_unit_handle == -1:
                self.is_sitting = True
                self.sprite.play_animation(game, UnitAnimState.Sit)
                return
            elif self.is_sitting:
                if game.engine.current_time - self.last_sit_heal_time > 2000:
                    self.last_sit_heal_time = game.engine.current_time
                    sit_heal_value = cast(0.1 * self.stats.hp.max, "Uint64")
                    self.stats.hp.inc(sit_heal_value)
                    # fully healed, not sitting anymore
                    if self.stats.hp.value_is_at_max():
                        self.is_sitting = False
                        self.sprite.play_animation(game, UnitAnimState.Idle)
                return

            tile_point = create_point(
                self.tile_point_hit_box.x, self.tile_point_hit_box.y)
            last_move_calc_diff = cast(
                game.engine.current_time - self.last_move_calc_time, "Uint32")
            last_attack_diff = cast(
                game.engine.current_time - self.last_attack_time, "Uint32")

            if not(self.is_ally_or_guild_faction()) and self.aggro_towards_unit_handle == -1 and game.engine.current_time > self.next_random_move_time:
                rand_interval = game.engine.get_rand_int(1000, 5000)
                rand_interval_u32 = cast(rand_interval, "Uint32")
                self.next_random_move_time = game.engine.current_time + rand_interval_u32
                map = game.world.maps.at(self.map_handle)
                random_move_dist = 20
                min_x = self.tile_point_hit_box.x - random_move_dist
                max_x = self.tile_point_hit_box.x + random_move_dist
                min_y = self.tile_point_hit_box.y - random_move_dist
                max_y = self.tile_point_hit_box.y + random_move_dist
                if min_x < 0:
                    min_x = 0
                if max_x > map.move_grid_rows - 1:
                    max_x = map.move_grid_rows - 1
                if min_y < 0:
                    min_y = 0
                if max_y > map.move_grid_cols - 1:
                    max_y = map.move_grid_cols - 1
                rand_x = game.engine.get_rand_int(min_x, max_x)
                rand_y = game.engine.get_rand_int(min_y, max_y)
                rand_tile_point = create_point(rand_x, rand_y)
                self.move_towards_tile_point(game, rand_tile_point)
            elif (self.is_ally_or_guild_faction() or self.aggro_nearest_unit) and self.aggro_towards_unit_handle == -1:
                self.aggro_towards_unit_handle = self.closest_opposite_unit_handle(
                    game)
            elif self.aggro_towards_unit_handle != -1:
                target_unit = game.world.units.at(
                    self.aggro_towards_unit_handle)
                # if the unit you were aggro'd against died, set your aggro handle to -1
                # will get a new target next frame.
                if target_unit.stats.hp.value_is_at_min():
                    self.aggro_towards_unit_handle = -1
                    return
                target_unit_tile_point = create_point(
                    target_unit.tile_point_hit_box.x, target_unit.tile_point_hit_box.y)
                dist = manhattan_distance(tile_point, target_unit_tile_point)
                # always use the first ability for now
                ability = self.get_ai_ability(game)
                if dist > ability.ability.stats.range and last_move_calc_diff > 1300:
                    self.last_move_calc_time = game.engine.current_time
                    aggro_unit = game.world.units.at(
                        self.aggro_towards_unit_handle)
                    aggro_unit_tile_point = create_point(
                        aggro_unit.tile_point_hit_box.x, aggro_unit.tile_point_hit_box.y)
                    self.move_towards_tile_point(
                        game, aggro_unit_tile_point)
                elif dist <= ability.ability.stats.range and last_attack_diff > self.stats.attack_speed.value:
                    # clear move tweens as we are in range
                    self.clear_move_tweens(game)
                    self.last_attack_time = game.engine.current_time
                    receiving_units = Array[int](10)
                    receiving_units.push_value(self.aggro_towards_unit_handle)
                    self.perform_ability(
                        game, ability, receiving_units)

    def update_merchant_ai(self, game: Game):
        if not(self.is_merchant()):
            print("Unit.update_merchant_ai. Unit is not a merchant.")
            exit(1)
        if self.ai_state == UnitAIState.MerchantRestocking:
            a = 0
        elif self.ai_state == UnitAIState.MerchantSelling:
            a = 0
        elif self.ai_state == UnitAIState.RandomTownMove:
            guild = game.world.guilds.at(self.guild_handle)
            if guild.inventory.has_merchant_sellable_items():
                self.ai_state = UnitAIState.MerchantRestocking
                self.move_to_guild_building(game)
            elif self.path_could_not_be_found:
                # couldn't find a random path, try again
                diff = game.engine.current_time - self.last_failed_path_time
                if diff > 2000:
                    self.move_to_random_town_point(game)
        else:
            # in a starting state, do random move, next frame the
            # unit ai state randomtownmove condition will trigger
            # and cancel the random move if the guild has inventory.
            self.move_to_random_town_point(game)

    def update_towns_person_ai(self, game: Game):
        if self.unit_type != UnitType.TownsPerson:
            print("Unit.update_towns_person_ai. Unit is not a towns person.")
            exit(1)
        if self.ai_state == UnitAIState.RandomTownMove:
            if game.engine.current_time > self.neutral_can_try_buy_again_time:
                diff = game.engine.current_time - self.last_try_merchant_buy_time
                success = False
                if diff > 2000:
                    self.last_try_merchant_buy_time = game.engine.current_time
                    success = self.try_find_and_move_to_merchant_shop(game)
                if not(success) and self.path_could_not_be_found:
                    # couldn't find a random path, try again
                    diff = game.engine.current_time - self.last_failed_path_time
                    if diff > 200:
                        self.move_to_random_town_point(game)
        elif self.ai_state == UnitAIState.MovingToBuyAtMerchant:
            a = 0
        else:
            # in a starting state, do random move, next frame the
            # unit ai state randomtownmove condition will trigger
            # and cancel the random move if the guild has inventory.
            self.move_to_random_town_point(game)

    def on_hit(self, game: Game, hit_by_unit_handle: int):
        if self.faction == Faction.Enemy and self.aggro_towards_unit_handle == -1:
            self.aggro_towards_unit_handle = hit_by_unit_handle

    def on_dead(self, game: Game, hit_by_unit_handle: int):
        self.aggro_towards_unit_handle = -1
        self.attacked_by_guild_handle = -1
        self.next_random_move_time = game.engine.current_time
        self.death_time = game.engine.current_time
        self.clear_move_tweens(game)

        # do item drops
        self.do_item_drops(game, hit_by_unit_handle)

    def set_random_spawn_point(self, game: Game):
        # requires the unit to have a valid map handle, so call unit.join_map()
        # before setting its random spawn point.
        map = game.world.maps.at(self.map_handle)
        spawn_tile_point = map.get_random_unoccupied_move_grid_tile_point(
            game, self.tile_point_hit_box)
        world_point = tile_point_to_world_point(
            spawn_tile_point, game.move_grid_tile_size)
        self.tile_point_hit_box.x = spawn_tile_point.x
        self.tile_point_hit_box.y = spawn_tile_point.y
        self.sprite.render_dst.dst.x = world_point.x
        self.sprite.render_dst.dst.y = world_point.y

    def set_spawn_point(self, game: Game, spawn_move_tile_point: SDL_Point):
        world_point = tile_point_to_world_point(
            spawn_move_tile_point, game.move_grid_tile_size)
        self.tile_point_hit_box.x = spawn_move_tile_point.x
        self.tile_point_hit_box.y = spawn_move_tile_point.y
        self.sprite.render_dst.dst.x = world_point.x
        self.sprite.render_dst.dst.y = world_point.y

    def is_ally_or_guild_faction(self):
        return self.faction == Faction.Ally or self.faction == Faction.Guild

    def closest_opposite_unit_handle(self, game: Game) -> int:
        map = game.world.maps.at(self.map_handle)
        min_dist = 100000
        min_dist_unit_handle = -1
        tile_point = create_point(
            self.tile_point_hit_box.x, self.tile_point_hit_box.y)
        for i in range(map.unit_handles.size):
            if i == self.handle:
                continue
            unit_handle = map.unit_handles[i]
            unit = game.world.units.at(unit_handle)
            if unit.faction == Faction.Neutral:
                continue
            # skip dead units
            if unit.stats.hp.value_is_at_min():
                continue
            if self.is_ally_or_guild_faction() and unit.is_ally_or_guild_faction():
                continue
            elif self.faction == Faction.Enemy and not(unit.is_ally_or_guild_faction()):
                continue
            # prevent ks
            elif unit.attacked_by_guild_handle != -1 and unit.attacked_by_guild_handle != self.guild_handle:
                continue
            unit_tile_point = create_point(
                unit.tile_point_hit_box.x, unit.tile_point_hit_box.y)
            dist = manhattan_distance(tile_point, unit_tile_point)
            if dist < min_dist:
                min_dist = dist
                min_dist_unit_handle = unit_handle
        return min_dist_unit_handle

    def warp_to_town_map(self, game: Game):
        current_map = game.world.maps.at(self.map_handle)
        if not(current_map.is_town_map):
            for i in range(game.world.maps_last_in_use_handle + 1):
                map = game.world.maps.at(i)
                if map.is_town_map:
                    self.join_map(game, map)
                    self.spawn_at_town_teleporter(game)
                    break

    def give_items_to_guild(self, game: Game):
        guild = game.world.guilds.at(self.guild_handle)
        for i, slot in enumerate(self.inventory.slots):
            # must check if slot is empty first, as the item ptr in shared item can be NULL
            # if the slot is empty and has never been set, when you try to use a NULL pointer
            # it will segfault.
            if slot.slot_is_empty:
                continue
            if slot.shared_item.item.item_type == ItemType.Misc:
                continue
            # add item to the guild's inventory
            guild.inventory.add_item(
                game, slot.shared_item.item.item_name, slot.shared_item.quantity)

            # remove item from slot
            self.inventory.clear_slot(i)

    def merchant_get_sellable_items_from_guild(self, game: Game):
        guild = game.world.guilds.at(self.guild_handle)
        for i, slot in enumerate(guild.inventory.slots):
            # must check if slot is empty first, as the item ptr in shared item can be NULL
            # if the slot is empty and has never been set, when you try to use a NULL pointer
            # it will segfault.
            if slot.slot_is_empty:
                continue
            # only selling useable items right now
            if slot.shared_item.item.item_type != ItemType.Useable:
                continue
            # add item to the guild's inventory
            self.inventory.add_item(
                game, slot.shared_item.item.item_name, slot.shared_item.quantity)

            # remove item from slot
            guild.inventory.clear_slot(i)

    def sell_items(self, game: Game):
        guild = game.world.guilds.at(self.guild_handle)
        for i, slot in enumerate(self.inventory.slots):
            # must check if slot is empty first, as the item ptr in shared item can be NULL
            # if the slot is empty and has never been set, when you try to use a NULL pointer
            # it will segfault.
            if slot.slot_is_empty:
                continue
            if slot.shared_item.item.item_type != ItemType.Misc:
                continue
            cost = slot.shared_item.item.cost
            quantity = slot.shared_item.quantity
            total_cost = cost * quantity
            guild.current_money += total_cost
            guild.total_money_earned += total_cost

            # remove item from slot
            self.inventory.clear_slot(i)

    def merchant_sell_to_unit(self, game: Game):
        guild = game.world.guilds.at(self.guild_handle)
        for i, slot in enumerate(self.inventory.slots):
            # must check if slot is empty first, as the item ptr in shared item can be NULL
            # if the slot is empty and has never been set, when you try to use a NULL pointer
            # it will segfault.
            if slot.slot_is_empty:
                continue
            if slot.shared_item.item.item_type != ItemType.Useable:
                continue
            cost = slot.shared_item.item.cost
            quantity = slot.shared_item.quantity
            total_cost = cost * quantity
            guild.current_money += total_cost
            guild.total_money_earned += total_cost

            # remove item from slot
            self.inventory.clear_slot(i)

            # only sell all of one item for now
            break
        # if the inventory is empty move randomly again (eventually the unit
        # will try to restock from the guild building)
        if self.inventory.inventory_is_empty():
            self.move_to_random_town_point(game)

    def change_to_sell_item_ai_state(self, game: Game):
        self.ai_state = UnitAIState.Selling
        self.aggro_towards_unit_handle = -1
        self.move_to_overworld_warp_point(game)

    def try_find_and_move_to_merchant_shop(self, game: Game) -> bool:
        map = game.world.maps.at(self.map_handle)
        move_options = MoveOptions()
        for i in range(map.unit_handles.size):
            unit_handle = map.unit_handles[i]
            unit = game.world.units.at(unit_handle)
            if unit.is_merchant() and unit.guild_handle != self.guild_handle and unit.unit_handle_buying_from_merchant == -1 and unit.ai_state == UnitAIState.MerchantSelling:
                self.ai_state = UnitAIState.MovingToBuyAtMerchant
                # units only buy one at a time, when they are done they will set the merchant's
                # neutral handle to -1.
                unit.unit_handle_buying_from_merchant = self.handle
                merchant_y_diff = 10
                unit_tile_point = create_point(
                    unit.tile_point_hit_box.x, unit.tile_point_hit_box.y + merchant_y_diff)
                if not(map.in_bounds_move_grid(unit_tile_point)):
                    unit_tile_point.y -= merchant_y_diff
                move_options.check_unit_collissions = False
                move_options.warp_point_handle = 0
                move_options.merchant_unit_handle = unit_handle
                self.move_to(game, unit_tile_point,
                             TweenType.UnitMoveToBuyAtMerchantShop, move_options)
                return True
        return False

    def move_to_random_town_point(self, game: Game):
        map = game.world.maps.at(self.map_handle)
        if not(map.is_town_map):
            unit_name_as_int = cast(self.unit_name, "int")
            faction_as_int = cast(self.faction, "int")
            print(
                "Unit.move_to_random_town_point. Not in a town map. handle:", self.handle, "\nmap handle:", self.map_handle, "\nunit_name:", unit_name_as_int, "\nfaction:", faction_as_int)
            exit(1)
        # set anim state back to idle in case they were sitting to sell
        self.sprite.anim_state = UnitAnimState.Idle
        self.ai_state = UnitAIState.RandomTownMove
        rand_tile_point = map.get_random_town_point(
            game, self.tile_point_hit_box)
        move_options = MoveOptions()
        move_options.check_unit_collissions = False
        move_options.warp_point_handle = 0
        self.move_to(game, rand_tile_point,
                     TweenType.UnitRandomTownMove, move_options)

    def move_to_guild_building(self, game: Game):
        map = game.world.maps.at(self.map_handle)
        move_options = MoveOptions()
        if not(map.is_town_map):
            print("Unit.move_to_shopt. Not in a town map.")
            exit(1)
        for i in range(map.building_handles.size):
            building_handle = map.building_handles[i]
            building = game.world.buildings.at(building_handle)
            if building.building_type == BuildingType.League:
                move_options.check_unit_collissions = False
                move_options.warp_point_handle = 0
                self.move_to(game, building.door_tile_point,
                             TweenType.UnitMoveToGuildBuilding, move_options)
                return
        print("Unit.move_to_guild_building. No guild building found.")
        exit(1)

    def move_to_shop(self, game: Game):
        map = game.world.maps.at(self.map_handle)
        move_options = MoveOptions()
        if not(map.is_town_map):
            print("Unit.move_to_shop. Not in a town map.")
            exit(1)
        for i in range(map.building_handles.size):
            building_handle = map.building_handles[i]
            building = game.world.buildings.at(building_handle)
            if building.is_shop:
                move_options.check_unit_collissions = False
                move_options.warp_point_handle = 0
                self.move_to(game, building.door_tile_point,
                             TweenType.UnitMoveToShop, move_options)
                return
        print("Unit.move_to_shop No shop found.")
        exit(1)

    def move_to_setup_merchant_shop(self, game: Game):
        map = game.world.maps.at(self.map_handle)
        if not(map.is_town_map):
            print("Unit.move_to_setup_merchant_shop Not in a town map.")
            exit(1)
        random_merchant_shop_point = map.get_random_merchant_shop_point(
            game, self.tile_point_hit_box)
        move_options = MoveOptions()
        move_options.check_unit_collissions = False
        move_options.warp_point_handle = 0
        self.move_to(game, random_merchant_shop_point,
                     TweenType.UnitMoveToSetupMerchantShop, move_options)

    def move_to_town_teleporter(self, game: Game):
        map = game.world.maps.at(self.map_handle)
        move_options = MoveOptions()
        if not(map.is_town_map):
            print(
                "Unit.move_to_town_teleporter. Unit is not in a town map. Map handle:", self.map_handle)
            exit(1)
        for i in range(map.building_handles.size):
            building_handle = map.building_handles[i]
            building = game.world.buildings.at(building_handle)
            if building.building_name == BuildingName.TeleportationStone:
                teleporter_tile_point = create_point(
                    building.tile_point_hit_box.x, building.tile_point_hit_box.y + building.tile_point_hit_box.h)
                move_options.check_unit_collissions = False
                move_options.warp_point_handle = 0
                self.move_to(game, teleporter_tile_point,
                             TweenType.UnitMoveToTeleporter, move_options)
                return
        print("Unit.move_to_town_teleporter. Town map doesn't have a teleporter.")
        exit(1)

    def move_to_overworld_warp_point(self, game: Game):
        map = game.world.maps.at(self.map_handle)
        move_options = MoveOptions()
        for i, warp_point in enumerate(map.warp_points):
            # overworld map is always handle 0
            if warp_point.warp_to_map_handle == 0:
                move_options.check_unit_collissions = False
                move_options.warp_point_handle = i
                self.move_to(game, warp_point.tile_point_move_grid,
                             TweenType.UnitMoveToWarpPoint, move_options)
                return
        print("Unit.move_to_overworld_warp_point. No overworld warp point found.")
        exit(1)

    def move_to_town_warp_point(self, game: Game):
        map = game.world.maps.at(self.map_handle)
        move_options = MoveOptions()
        for i, warp_point in enumerate(map.warp_points):
            # overworld map is always handle 0
            if warp_point.warp_to_map_handle == 2:
                move_options.check_unit_collissions = False
                move_options.warp_point_handle = i
                self.move_to(game, warp_point.tile_point_move_grid,
                             TweenType.UnitMoveToWarpPoint, move_options)
                return
        print("Unit.move_to_town_warp_point. No town warp point found.")
        exit(1)

    def move_to_battle_warp_point(self, game: Game):
        if self.battle_map_handle == -1:
            print("Unit.move_to_battle_warp_piont. battle_map_handle is -1.")
            exit(1)
        map = game.world.maps.at(self.map_handle)
        move_options = MoveOptions()
        for i, warp_point in enumerate(map.warp_points):
            # overworld map is always handle 0
            if warp_point.warp_to_map_handle == self.battle_map_handle:
                move_options.check_unit_collissions = False
                move_options.warp_point_handle = i
                self.move_to(game, warp_point.tile_point_move_grid,
                             TweenType.UnitMoveToWarpPoint, move_options)
                return
        print("Unit.move_to_battle_warp_point. No battle warp point found. Battle map handle:",
              self.battle_map_handle)
        exit(1)

    def spawn_at_town_teleporter(self, game: Game):
        map = game.world.maps.at(self.map_handle)
        if not(map.is_town_map):
            print(
                "Unit.spawn_at_town_teleporter. Unit is in a non-town map. Only town maps have teleporters.")
            exit(1)
        for building_handle_ptr in map.building_handles:
            building_handle = deref(building_handle_ptr)
            building = game.world.buildings.at(building_handle)
            if building.building_name == BuildingName.TeleportationStone:
                spawn_tile_point = create_point(
                    building.tile_point_hit_box.x, building.tile_point_hit_box.y + building.tile_point_hit_box.h)
                world_point = tile_point_to_world_point(
                    spawn_tile_point, game.move_grid_tile_size)
                self.tile_point_hit_box.x = spawn_tile_point.x
                self.tile_point_hit_box.y = spawn_tile_point.y
                self.sprite.render_dst.dst.x = world_point.x
                self.sprite.render_dst.dst.y = world_point.y
                return
        print("Unit.spawn_at_town_teleporter. Town map doesn't have a teleporter.")
        exit(1)

    def perform_ability(self, game: Game, ability_to_perform: SharedAbility, target_unit_handles):
        map = game.world.maps.at(self.map_handle)
        self.sprite.play_animation(game, UnitAnimState.Cast)
        for i in range(target_unit_handles.size):
            target_unit_handle = target_unit_handles[i]
            target_unit = game.world.units.at(target_unit_handle)
            ability_handle = game.world.get_handle(HandleType.Ability)
            ability = game.world.abilities.at(ability_handle)
            ability.set_to(game, ability_to_perform.ability.ability_name)
            map.ability_handles.push_value(ability_handle)
            tween_handle = game.world.get_handle(HandleType.TweenXY)
            tween = game.world.tween_xys.at(tween_handle)
            callback = TweenCallback()
            callback.tween_type = TweenType.PerformAbility
            callback.handle = ability_handle
            callback.handle_type = HandleType.Ability
            callback.acting_unit_handle = self.handle
            callback.receiving_unit_handle = target_unit_handle
            callback.map_handle = self.map_handle
            # only used if the ability is not a projectile
            ability_srcs_size = ability.ability.sprite.srcs.size
            ability_anim_speed = ability.ability.sprite.anim_speed
            ability_duration = ability_srcs_size * ability_anim_speed
            duration = cast(ability_duration, "Uint32")
            start_rect = self.sprite.render_dst.dst
            # use the target unit's sprite dst's ptr so that constant tweens can
            # move towards it. If it was a copy of a local the stack would be cleared
            # before the tween made use of the pointer.
            target_rect_ptr = addr(target_unit.sprite.render_dst.dst)
            start_rect.x += ability.ability.start_offset.x
            start_rect.y += ability.ability.start_offset.y
            if not(ability.ability.is_projectile):
                start_rect = deref(target_rect_ptr)
            # set the ability sprite's dst to start rect
            ability.render_dst.dst = start_rect
            tween.set(game, start_rect, ability.render_dst.dst, target_rect_ptr,
                      ability.ability.is_projectile, ability.ability.projectile_speed, duration,
                      ability.ability.delay, callback)

    def do_item_drops(self, game: Game, target_unit_handle: int):
        target_unit = game.world.units.at(target_unit_handle)
        for item_drop in self.item_drops:
            rand_int = game.engine.get_rand_int(0, 100)
            if rand_int < item_drop.drop_chance:
                map = game.world.maps.at(self.map_handle)
                item_handle = game.world.get_handle(HandleType.Item)
                item = game.world.items.at(item_handle)
                # quantity and drop chance don't matter here, but I don't want a separate set
                # to function for item drops.
                item.set_to(game, item_drop.item.item_name,
                            item_drop.quantity, item_drop.drop_chance)
                map.item_handles.push_value(item_handle)
                tween_handle = game.world.get_handle(HandleType.TweenXY)
                tween = game.world.tween_xys.at(tween_handle)
                callback = TweenCallback()
                callback.tween_type = TweenType.ItemDrop
                callback.handle = item_handle
                callback.receiving_unit_handle = target_unit_handle
                callback.map_handle = self.map_handle
                delay = cast(0, "Uint32")
                duration = cast(0, "Uint32")
                start_rect = self.sprite.render_dst.dst
                target_rect_ptr = addr(target_unit.sprite.render_dst.dst)
                item.render_dst.dst = start_rect
                tween.set(game, start_rect, item.render_dst.dst, target_rect_ptr,
                          True, 1.5, duration, delay, callback)

    def move_towards_tile_point(self, game: Game, target_point: SDL_Point):
        map = game.world.maps.at(self.map_handle)
        unit_tile_point = create_point(
            self.tile_point_hit_box.x, self.tile_point_hit_box.y)
        # find closest point to target unit handle
        game.world.path_finder.set_path(
            game, map, self, unit_tile_point, target_point, True)
        # move towards closest point to target unit handle
        move_options = MoveOptions()
        move_options.check_unit_collissions = True
        move_options.warp_point_handle = 0
        self.move_to(
            game, game.world.path_finder.closest_point_to_target, TweenType.UnitMove, move_options)

    def clear_move_tweens(self, game: Game):
        game.world.remove_all_tweens_with_higher_level_type(
            TweenHigherLevelType.Move, self.handle)

    def move_to(self, game: Game, target_point: SDL_Point, move_tween_type: TweenType, move_options: MoveOptions):
        # clear previous move tweens (can be expensive, maybe check if the unit is moving first)
        self.clear_move_tweens(game)
        unit_tile_point = create_point(
            self.tile_point_hit_box.x, self.tile_point_hit_box.y)
        map = game.world.maps.at(self.map_handle)
        game.world.path_finder.set_path(
            game, map, self, unit_tile_point, target_point, move_options.check_unit_collissions)
        if game.world.path_finder.path.size == 0:
            # mark the time when a path couldn't be found
            self.last_failed_path_time = game.engine.current_time
            self.path_could_not_be_found = True
            unit_name_as_int = cast(self.unit_name, "int")
            faction_as_int = cast(self.faction, "int")
            print("Path size is 0.\nunit handle:", self.handle, "\nmap handle:", self.map_handle, "\nunit name:",
                  unit_name_as_int, "\nfaction", faction_as_int, "\np.x", self.tile_point_hit_box.x, "\np.y", self.tile_point_hit_box.y, "\nt.x", target_point.x, "\nt.y", target_point.y)
            return
        else:
            self.path_could_not_be_found = False

        # set unit anim state to walk (idle is walk for now)
        self.sprite.anim_state = UnitAnimState.Idle

        walk_speed = 30
        # make overworld walk speed slower
        if map.handle == 0:
            walk_speed = 45
        prev_point = create_point(
            self.tile_point_hit_box.x, self.tile_point_hit_box.y)
        for i, p in enumerate(game.world.path_finder.path):
            path_tile_point = deref(p)
            duration = cast(walk_speed, "Uint32")
            delay = cast(i * walk_speed, "Uint32")
            prev_world_point = tile_point_to_world_point(
                prev_point, game.move_grid_tile_size)
            world_point = tile_point_to_world_point(
                p, game.move_grid_tile_size)
            prev_world_point_rect = create_rect(
                prev_world_point.x, prev_world_point.y, 0, 0)
            world_point_rect = create_rect(world_point.x, world_point.y, 0, 0)
            tween_handle = game.world.get_handle(HandleType.TweenXY)
            tween = game.world.tween_xys.at(tween_handle)
            callback = TweenCallback()
            callback.tween_higher_level_type = TweenHigherLevelType.Move
            callback.tween_type = move_tween_type
            callback.handle = self.handle
            callback.handle_type = HandleType.Unit
            callback.tile_point = path_tile_point
            callback.warp_point_handle = move_options.warp_point_handle
            callback.merchant_unit_handle = move_options.merchant_unit_handle
            callback.is_final_point_in_path = i == game.world.path_finder.path.size - 1
            tween.set(game, prev_world_point_rect, self.sprite.render_dst.dst,
                      world_point_rect, False, 0.0, duration, delay, callback)
            prev_point = path_tile_point

    def get_ability(self, ability_name: AbilityName) -> SharedAbility:
        for ability in self.abilities:
            if ability.ability.ability_name == ability_name:
                return ability

        ability_name_as_int = cast(ability_name, "int")
        print("Unit.get_ability. ability not found. AbilityName:",
              ability_name_as_int)
        exit(1)

    def get_ability_skill_points(self, ability_name: AbilityName) -> int:
        for ability in self.abilities:
            if ability.ability.ability_name == ability_name:
                return ability.skill_points
        return 0

    def is_ability_learned(self, ability_name: AbilityName) -> bool:
        for ability in self.abilities:
            if ability.ability.ability_name == ability_name:
                return True
        return False

    def get_ai_ability(self, game: Game) -> SharedAbility:
        for ai_ability in self.ai_abilities:
            if ai_ability.is_empty:
                continue
            ability_handle = ai_ability.unit_ability_handle
            return self.abilities.at(ability_handle)
        # no ai abilities were triggered, use the default attack ability
        return addr(self.default_attack_ability)

    def set_to(self, game: Game, unit_name: UnitName, faction: Faction):
        # clear previous data
        self.job_abilities.clear()
        self.abilities.clear()
        self.item_drops.clear()
        # set new data
        self.unit_name = unit_name
        self.faction = faction
        self.sprite.set_to(game, unit_name)
        # unit sprite's size dims have been set in sprite.set_to, so we can set tile_point_hit_box's w, h
        # unit.tile_point_hit_box x, y is the tile point, w, h is the size dims of the unit (its collider)
        # the rectangle must fit perfectly into grid tile size, so its w, h mod the move tile grid size
        # must be 0.
        # Example, 0, 0, 40, 40 with a grid size of 2,2 means the unit takes up 0, 0, 20, 20, i.e.
        # index 0, 0 is the top left corner, idx 0, 20 is top right corner, idx 20, 20 is bottom  right corner.
        if mod(self.sprite.hit_box_size.x, game.move_grid_tile_size.x) != 0:
            print(
                "Unit.set_to - sprite's hit_box's width mod grid tile size != 0.", "width:",
                self.sprite.hit_box_size.x, "grid tile size:", game.move_grid_tile_size.x)
            exit(1)
        if mod(self.sprite.hit_box_size.y, game.move_grid_tile_size.y) != 0:
            print("Unit.set_to - sprite's hit_box's height mod grid tile size != 0.", "height:",
                  self.sprite.hit_box_size.y, "grid tile size:", game.move_grid_tile_size.y)
            exit(1)
        move_grid_hit_box_size_dims = get_move_grid_size_dims(
            self.sprite.hit_box_size.x, self.sprite.hit_box_size.y, game.move_grid_tile_size)
        self.tile_point_hit_box.w = move_grid_hit_box_size_dims.x
        self.tile_point_hit_box.h = move_grid_hit_box_size_dims.y

        self.respawn_time = 10000
        stats_min = cast(0, "Uint64")
        stats_current = cast(10, "Uint64")
        stats_max = cast(99, "Uint64")
        hp_max_value = cast(9999999, "Uint64")
        experience_max_value = cast(9999999, "Uint64")
        attack_speed_max_value = cast(10000, "Uint64")
        self.stats.level = 1
        self.stats.job_level = 1
        self.stats.experience_drop = 5
        self.stats.job_experience_drop = 2
        self.stats.experience.set(stats_min, stats_min, experience_max_value)
        self.stats.job_experience.set(
            stats_min, stats_min, experience_max_value)
        self.stats.experience.max = cast(100, "Uint64")
        self.stats.job_experience.max = cast(30, "Uint64")
        self.stats.strength.set_with_max_to_upper_bound(
            stats_min, stats_current, stats_max)
        self.stats.intelligence.set_with_max_to_upper_bound(
            stats_min, stats_current, stats_max)
        self.stats.dexterity.set_with_max_to_upper_bound(
            stats_min, stats_current, stats_max)
        self.stats.vitality.set_with_max_to_upper_bound(
            stats_min, stats_current, stats_max)
        self.stats.agility.set_with_max_to_upper_bound(
            stats_min, stats_current, stats_max)
        self.stats.luck.set_with_max_to_upper_bound(
            stats_min, stats_current, stats_max)
        self.default_attack_ability.set_to(game, AbilityName.MeleeAttack)
        if unit_name == UnitName.RandomTownsPerson0:
            # towns people are always neutral faction
            self.faction = Faction.Neutral
            self.unit_type = UnitType.TownsPerson
            self.display_name.string_set_literal("Villager")
            # give the neutral unit some hp so that its not dead. If its dead
            # it won't appear.
            self.stats.hp.set(cast(0, "Uint64"), cast(
                10, "Uint64"), hp_max_value)
        elif unit_name == UnitName.Merchant:
            self.display_name.string_set_literal("Merchant")
            self.stats.hp.set(cast(0, "Uint64"), cast(
                500, "Uint64"), hp_max_value)
            self.stats.attack_speed.set(cast(0, "Uint64"), cast(
                2000, "Uint64"), attack_speed_max_value)
        elif unit_name == UnitName.Explorer:
            self.display_name.string_set_literal("Explorer")
            self.stats.hp.set(cast(0, "Uint64"), cast(
                500, "Uint64"), hp_max_value)
            self.stats.attack_speed.set(cast(0, "Uint64"), cast(
                2000, "Uint64"), attack_speed_max_value)
        elif unit_name == UnitName.Mage:
            self.display_name.string_set_literal("Mage")
            job_abilitiy = self.job_abilities.next()
            job_abilitiy.set_to(game, AbilityName.Fire)
            game.temp_ability.set_to(game, AbilityName.Fire)
            ability = self.abilities.next()
            ability.set_to(game, AbilityName.Fire)
            print(self.ai_abilities.size)
            unit_ai_ability = self.ai_abilities.at(0)
            unit_ai_ability.set(0, AIAbilityCondition.Always)
            self.stats.hp.set(cast(0, "Uint64"), cast(
                500, "Uint64"), hp_max_value)
            self.stats.attack_speed.set(cast(0, "Uint64"), cast(
                4000, "Uint64"), attack_speed_max_value)
        elif unit_name == UnitName.Wizard:
            self.display_name.string_set_literal("Wizard")
            job_abilitiy = self.job_abilities.next()
            job_abilitiy.set_to(game, AbilityName.Fire)
            ability = self.abilities.next()
            ability.set_to(game, AbilityName.Fire)
            unit_ai_ability = self.ai_abilities.at(0)
            unit_ai_ability.set(0, AIAbilityCondition.Always)
            self.stats.hp.set(cast(0, "Uint64"), cast(
                500, "Uint64"), hp_max_value)
            self.stats.attack_speed.set(cast(0, "Uint64"), cast(
                4000, "Uint64"), attack_speed_max_value)
        elif unit_name == UnitName.Scholar:
            self.display_name.string_set_literal("Scholar")
            job_abilitiy = self.job_abilities.next()
            job_abilitiy.set_to(game, AbilityName.Fire)
            ability = self.abilities.next()
            ability.set_to(game, AbilityName.Fire)
            unit_ai_ability = self.ai_abilities.at(0)
            unit_ai_ability.set(0, AIAbilityCondition.Always)
            self.stats.hp.set(cast(0, "Uint64"), cast(
                500, "Uint64"), hp_max_value)
            self.stats.attack_speed.set(cast(0, "Uint64"), cast(
                4000, "Uint64"), attack_speed_max_value)
        elif unit_name == UnitName.Slime:
            self.display_name.string_set_literal("Slyme")
            ability = self.abilities.next()
            ability.set_to(game, AbilityName.MeleeAttack)
            game.temp_shared_item.set_to(game, ItemName.Jelly, 1, 75)
            self.item_drops.push(game.temp_shared_item)
            game.temp_shared_item.set_to(game, ItemName.Apple, 1, 100)
            self.item_drops.push(game.temp_shared_item)
            self.stats.experience_drop = 3
            self.stats.job_experience_drop = 1
            self.stats.hp.set(cast(0, "Uint64"), cast(
                40, "Uint64"), hp_max_value)
            self.stats.attack_speed.set(cast(0, "Uint64"), cast(
                2000, "Uint64"), attack_speed_max_value)
        elif unit_name == UnitName.Bunny:
            self.display_name.string_set_literal("Rabyt")
            ability = self.abilities.next()
            ability.set_to(game, AbilityName.MeleeAttack)
            game.temp_shared_item.set_to(game, ItemName.FurPelt, 1, 75)
            self.item_drops.push(game.temp_shared_item)
            game.temp_shared_item.set_to(game, ItemName.Apple, 1, 100)
            self.item_drops.push(game.temp_shared_item)
            self.stats.experience_drop = 5
            self.stats.job_experience_drop = 2
            self.stats.hp.set(cast(0, "Uint64"), cast(
                40, "Uint64"), hp_max_value)
            self.stats.attack_speed.set(cast(0, "Uint64"), cast(
                2000, "Uint64"), attack_speed_max_value)
        elif unit_name == UnitName.Bat:
            self.display_name.string_set_literal("Bat")
            ability = self.abilities.next()
            ability.set_to(game, AbilityName.MeleeAttack)
            game.temp_shared_item.set_to(game, ItemName.BatWing, 1, 75)
            self.item_drops.push(game.temp_shared_item)
            self.stats.experience_drop = 4
            self.stats.job_experience_drop = 2
            self.stats.hp.set(cast(0, "Uint64"), cast(
                40, "Uint64"), hp_max_value)
            self.stats.attack_speed.set(cast(0, "Uint64"), cast(
                2000, "Uint64"), attack_speed_max_value)
        elif unit_name == UnitName.Stump:
            self.display_name.string_set_literal("Stump")
            ability = self.abilities.next()
            ability.set_to(game, AbilityName.MeleeAttack)
            game.temp_shared_item.set_to(game, ItemName.Branch, 1, 75)
            self.item_drops.push(game.temp_shared_item)
            game.temp_shared_item.set_to(game, ItemName.Apple, 1, 100)
            self.item_drops.push(game.temp_shared_item)
            self.stats.experience_drop = 12
            self.stats.job_experience_drop = 5
            self.stats.hp.set(cast(0, "Uint64"), cast(
                40, "Uint64"), hp_max_value)
            self.stats.attack_speed.set(cast(0, "Uint64"), cast(
                2000, "Uint64"), attack_speed_max_value)
        elif unit_name == UnitName.Shroomed:
            self.display_name.string_set_literal("Shroomed")
            ability = self.abilities.next()
            ability.set_to(game, AbilityName.MeleeAttack)
            game.temp_shared_item.set_to(game, ItemName.Mushroom, 1, 75)
            self.item_drops.push(game.temp_shared_item)
            game.temp_shared_item.set_to(game, ItemName.Apple, 1, 100)
            self.item_drops.push(game.temp_shared_item)
            self.stats.experience_drop = 9
            self.stats.job_experience_drop = 4
            self.stats.hp.set(cast(0, "Uint64"), cast(
                40, "Uint64"), hp_max_value)
            self.stats.attack_speed.set(cast(0, "Uint64"), cast(
                2000, "Uint64"), attack_speed_max_value)
        else:
            unit_name_as_int = cast(unit_name, "int")
            print("Unit.set_to. Unit name not handled. UnitName:",
                  unit_name_as_int)
            exit(1)

        # update ui with unit values
        text_color = get_faction_color(faction)
        self.display_name_text.text_set_color(game, text_color)
        self.guild_display_name_text.text_set_color(game, text_color)
        self.display_name_text.str.string_set(self.display_name)
