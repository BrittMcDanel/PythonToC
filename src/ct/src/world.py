from ct.src.ct_array import find_and_remove_handle, pool_get_next_in_use_handle, pool_init, pool_of_text_init, pool_release_handle
from ct.src.image import *
from ct.src.utils import SDL_Rect, SDL_Point, create_color, get_stat_cost, get_stat_points_for_level, points_are_equal, tile_point_to_world_point, tile_point_to_move_grid_tile_point, world_point_to_index_with_camera
from ct.src.image import Image
from ct.src.base_types import Array, sprintf, array_get_buffer, cast, addr, deref, set, array_capacity, rev_range, Any
from ct.src.unit import Unit
from ct.src.map import Map
from ct.src.utils import create_point
from ct.src.constants import BuildingName, UnitAnimState, BGMAudioName, TweenHigherLevelType, UnitAIState, UnitName, SDLK, Faction, HandleType, TweenType, FontStyle, TextAlignment, TextWordWrap
from ct.src.guild import Guild
from ct.src.building import Building
from ct.src.tween import TweenCallback, TweenXY
from ct.src.path_finder import PathFinder
from ct.src.ability import Ability
from ct.src.shared_ability import SharedAbility
from ct.src.shared_item import SharedItem
from ct.src.text import TextSM, TextLG, text_set
from ct.src.ui import UI
from ct.src.game_data import GameData
# weak imports
from ct.src.game import Game


class World:
    def __init__(self):
        self.ui: UI = None
        self.maps: Array[Map] = Array[Map](100)
        self.buildings: Array[Building] = Array[Building](2000)
        self.units: Array[Unit] = Array[Unit](3000)
        self.guilds: Array[Guild] = Array[Guild](100)
        self.items: Array[SharedItem] = Array[SharedItem](5000)
        self.abilities: Array[SharedAbility] = Array[SharedAbility](5000)
        self.damage_texts: Array[TextSM] = Array[TextSM](5000)
        self.tween_xys: Array[TweenXY] = Array[TweenXY](20000)
        self.maps_last_in_use_handle: int = None
        self.buildings_last_in_use_handle: int = None
        self.units_last_in_use_handle: int = None
        self.guilds_last_in_use_handle: int = None
        self.items_last_in_use_handle: int = None
        self.abilities_last_in_use_handle: int = None
        self.damage_texts_last_in_use_handle: int = None
        self.tween_xys_last_in_use_handle: int = None
        self.visible_map_handle: int = None
        self.path_finder: PathFinder = None
        self.mouse_down_tile_point: SDL_Point = None

    def init(self, game: Game):
        self.ui.init(game)
        pool_init(game, self.maps, addr(self.maps_last_in_use_handle))
        pool_init(game, self.buildings, addr(
            self.buildings_last_in_use_handle))
        pool_init(game, self.units, addr(self.units_last_in_use_handle))
        pool_init(game, self.guilds, addr(self.guilds_last_in_use_handle))
        pool_init(game, self.items, addr(
            self.items_last_in_use_handle))
        pool_init(game, self.abilities, addr(
            self.abilities_last_in_use_handle))
        pool_of_text_init(game, self.damage_texts, addr(
            self.damage_texts_last_in_use_handle))
        pool_init(game, self.tween_xys, addr(
            self.tween_xys_last_in_use_handle))
        # don't initially show the overworld map for now
        self.visible_map_handle = 1

        # bgm_audio = game.engine.get_bgm_audio(BGMAudioName.Forest)
        # game.engine.audio_play_bgm(bgm_audio)
        # game.engine.audio_set_bgm_volume(0.3)

        self.create_initial_maps(game)
        self.create_guilds(game)
        self.create_initial_units(game)

    def update(self, game: Game):
        mouse_tile_point = world_point_to_index_with_camera(
            game.engine.mouse_point_scaled, game.engine.camera.dst, game.tile_size)
        mouse_move_grid_tile_point = world_point_to_index_with_camera(
            game.engine.mouse_point_scaled, game.engine.camera.dst, game.move_grid_tile_size)
        w_int = cast(SDLK.w, "int")
        a_int = cast(SDLK.a, "int")
        s_int = cast(SDLK.s, "int")
        d_int = cast(SDLK.d, "int")
        q_int = cast(SDLK.q, "int")
        e_int = cast(SDLK.e, "int")
        z_int = cast(SDLK.z, "int")
        w_down = game.engine.keys_held_down[w_int]
        a_down = game.engine.keys_held_down[a_int]
        s_down = game.engine.keys_held_down[s_int]
        d_down = game.engine.keys_held_down[d_int]
        q_down = game.engine.keys_down[q_int]
        e_down = game.engine.keys_down[e_int]
        z_down = game.engine.keys_down[z_int]
        camera_move_dist = 4

        if e_down:
            player_guild = self.guilds.at(0)
            unit_handle = player_guild.unit_handles[0]
            unit = self.units.at(unit_handle)
            if unit.unit_name == UnitName.Explorer:
                unit.stats.job_level = 10
            elif unit.unit_name == UnitName.Mage:
                unit.stats.job_level = 40
        if z_down:
            player_guild = self.guilds.at(0)
            unit_handle = player_guild.unit_handles[0]
            unit = self.units.at(unit_handle)
            stat_points = get_stat_points_for_level(unit.stats.level)
            stat_point_cost = get_stat_cost(unit.stats.strength.value)
            print(unit.stats.level, stat_points, "-",
                  unit.stats.strength.value, stat_point_cost)
            unit.available_stat_points += get_stat_points_for_level(
                unit.stats.level)
            unit.stats.level += 1
            uint64_1 = cast(1, "Uint64")
            unit.stats.strength.inc(uint64_1)
        if w_down:
            game.engine.camera.dst.y -= camera_move_dist
        if a_down:
            game.engine.camera.dst.x -= camera_move_dist
        if s_down:
            game.engine.camera.dst.y += camera_move_dist
        if d_down:
            game.engine.camera.dst.x += camera_move_dist

        if game.engine.is_mouse_down:
            self.mouse_down_tile_point = mouse_tile_point
        if game.engine.is_mouse_up:
            # is a click if the mouse is down and up on the same tile
            if points_are_equal(self.mouse_down_tile_point, mouse_tile_point):
                # find map the user clicked on in the overworld
                if self.visible_map_handle == 0:
                    overworld = self.maps.at(0)
                    for warp_point in overworld.warp_points:
                        if points_are_equal(mouse_tile_point, warp_point.tile_point):
                            self.visible_map_handle = warp_point.warp_to_map_handle
                            break
        if game.engine.is_right_mouse_down:
            if self.visible_map_handle != 0:
                self.visible_map_handle = 0

        # clear ui before everything is updated, which refills the ui rect buffer
        self.ui.clear()

        # update tweens
        self.update_tween_arr(
            game, self.tween_xys, self.tween_xys_last_in_use_handle, HandleType.TweenXY)

        # if the last handle is 0 then iterate to 1
        for i in range(self.units_last_in_use_handle + 1):
            unit = self.units.at(i)
            if not(unit.in_use_in_pool):
                continue
            unit.update(game)
        for i in range(self.items_last_in_use_handle + 1):
            item = self.items.at(i)
            if not(item.in_use_in_pool):
                continue
            item.update(game)
        for i in range(self.abilities_last_in_use_handle + 1):
            ability = self.abilities.at(i)
            if not(ability.in_use_in_pool):
                continue
            ability.update(game)
        for i in range(self.damage_texts_last_in_use_handle + 1):
            damage_text = self.damage_texts.at(i)
            if not(damage_text.in_use_in_pool):
                continue
            damage_text.text_update(game)
        for map in self.maps:
            map.update(game)

        # call update_visible_map for the visible map
        visible_map = self.maps.at(self.visible_map_handle)
        visible_map.update_visible_map(game)

        # everything has been updated, so the ui buffer is populated
        # if any ui was meant to appear, update ui now.
        self.ui.update(game)

    def draw(self, game: Game):
        visible_map = self.maps.at(self.visible_map_handle)
        visible_map.draw(game)
        # draw ui
        self.ui.draw(game)

    def update_tween_arr(self, game: Game, arr: Any, last_in_use_handle: int, tween_handle_type: HandleType):
        # updates any tween arr
        for i in range(last_in_use_handle + 1):
            tween = arr.at(i)
            if not(tween.in_use_in_pool):
                continue
            tween_completed = tween.update(game)
            if tween_completed.initial_has_started:
                self.handle_tween_on_start(game, tween.callback)
            if tween_completed.completed:
                self.handle_tween_on_complete(game, tween.callback)
                # on_complete could have a callback that already released this handle,
                # if its been released after on_complete then don't release it again.
                if tween.in_use_in_pool:
                    self.release_handle(tween_handle_type, i)

    def remove_all_tweens_with_higher_level_type(self, tween_higher_level_type: TweenHigherLevelType, handle: int):
        for i in range(self.tween_xys_last_in_use_handle + 1):
            tween = self.tween_xys.at(i)
            if not(tween.in_use_in_pool):
                continue
            if tween.callback.tween_higher_level_type == tween_higher_level_type and tween.callback.handle == handle:
                self.release_handle(HandleType.TweenXY, i)

    def remove_all_tweens(self, tween_type: TweenType, handle_type: HandleType, handle: int):
        # does not remove tweens, but sets their remove_in_update flag to True for the tween update function
        # to remove when it is called.
        for i in range(self.tween_xys_last_in_use_handle + 1):
            tween = self.tween_xys.at(i)
            if not(tween.in_use_in_pool):
                continue
            if tween.callback.tween_type == tween_type and tween.callback.handle_type == handle_type and tween.callback.handle == handle:
                # cannot remove the tween here as it may be called while already iterating the tween array
                # in an outer function. So, set a flag telling the outer update loop either this frame or
                # the next frame to remove this tween and to not process it.
                self.release_handle(HandleType.TweenXY, i)

    def handle_tween_on_start(self, game: Game, tween_callback: TweenCallback):
        if tween_callback.tween_type == TweenType.NA:
            print("World - handle_tween_on_start. tween_type is NA.")
            exit(1)
        elif tween_callback.tween_higher_level_type == TweenHigherLevelType.Move:
            if tween_callback.tween_type == TweenType.UnitMove:
                unit_handle = tween_callback.handle
                unit = self.units.at(unit_handle)
                map = self.maps.at(unit.map_handle)
                # if the unit were to move to this tile, see if they would collide with any other unit on the map.
                # if they would, remove all move tweens as this unit needs to find a new path.
                unit_tile_point_hit_box_cpy = unit.tile_point_hit_box
                unit_tile_point_hit_box_cpy.x = tween_callback.tile_point.x
                unit_tile_point_hit_box_cpy.y = tween_callback.tile_point.y
                if map.unit_occupies_tile_point_move_grid(game, unit_tile_point_hit_box_cpy, unit_handle):
                    self.remove_all_tweens(
                        tween_callback.tween_type, tween_callback.handle_type, tween_callback.handle)
                else:
                    unit.tile_point_hit_box.x = tween_callback.tile_point.x
                    unit.tile_point_hit_box.y = tween_callback.tile_point.y
            else:
                # don't need to check for unit collissions on town maps as they can collide with each other
                unit_handle = tween_callback.handle
                unit = self.units.at(unit_handle)
                unit.tile_point_hit_box.x = tween_callback.tile_point.x
                unit.tile_point_hit_box.y = tween_callback.tile_point.y

    def handle_tween_on_complete(self, game: Game, tween_callback: TweenCallback):
        callback = TweenCallback()
        if tween_callback.tween_type == TweenType.NA:
            print("World - handle_tween_on_complete. tween_type is NA.")
            exit(1)
        elif tween_callback.tween_type == TweenType.UnitMoveToShop:
            if tween_callback.is_final_point_in_path:
                unit = self.units.at(tween_callback.handle)
                unit.inside_building = True
                # basically a set delay for in shop
                tween_handle = game.world.get_handle(HandleType.TweenXY)
                tween = game.world.tween_xys.at(tween_handle)
                callback.tween_type = TweenType.UnitInShop
                callback.handle = unit.handle
                duration = cast(2000, "Uint32")
                delay = cast(0, "Uint32")
                tween.set(game, unit.sprite.render_dst.dst, unit.sprite.render_dst.dst,
                          unit.sprite.render_dst.dst, False, 0.0, duration, delay, callback)
        elif tween_callback.tween_type == TweenType.UnitInShop:
            unit = self.units.at(tween_callback.handle)
            # sell items
            unit.sell_items(game)
            unit.inside_building = False
            success = unit.try_find_and_move_to_merchant_shop(game)
            if not(success):
                unit.ai_state = UnitAIState.Battle
                unit.move_to_overworld_warp_point(game)
        elif tween_callback.tween_type == TweenType.UnitMoveToTeleporter:
            if tween_callback.is_final_point_in_path:
                unit = self.units.at(tween_callback.handle)
                battle_map = self.maps.at(unit.battle_map_handle)
                unit.join_map(game, battle_map)
                unit.set_random_spawn_point(game)
        elif tween_callback.tween_type == TweenType.UnitMoveToGuildBuilding:
            if tween_callback.is_final_point_in_path:
                unit = self.units.at(tween_callback.handle)
                unit.inside_building = True
                # basically a set delay for in guild building
                tween_handle = game.world.get_handle(HandleType.TweenXY)
                tween = game.world.tween_xys.at(tween_handle)
                callback.tween_type = TweenType.UnitInGuildBuilding
                callback.handle = unit.handle
                duration = cast(2000, "Uint32")
                delay = cast(0, "Uint32")
                tween.set(game, unit.sprite.render_dst.dst, unit.sprite.render_dst.dst,
                          unit.sprite.render_dst.dst, False, 0.0, duration, delay, callback)
        elif tween_callback.tween_type == TweenType.UnitInGuildBuilding:
            unit = self.units.at(tween_callback.handle)
            unit.inside_building = False
            # give non-sellable items to the guild's inventory
            if unit.is_merchant():
                unit.merchant_get_sellable_items_from_guild(game)
                unit.move_to_setup_merchant_shop(game)
            else:
                unit.give_items_to_guild(game)
                unit.move_to_shop(game)
        elif tween_callback.tween_type == TweenType.UnitMoveToSetupMerchantShop:
            if tween_callback.is_final_point_in_path:
                unit = self.units.at(tween_callback.handle)
                unit.ai_state = UnitAIState.MerchantSelling
                unit.sprite.play_animation(game, UnitAnimState.Sit)
        elif tween_callback.tween_type == TweenType.UnitRandomTownMove:
            if tween_callback.is_final_point_in_path:
                unit = self.units.at(tween_callback.handle)
                # start the random move point cycle again
                unit.move_to_random_town_point(game)
        elif tween_callback.tween_type == TweenType.UnitMoveToWarpPoint:
            if tween_callback.is_final_point_in_path:
                unit = self.units.at(tween_callback.handle)
                map = self.maps.at(unit.map_handle)
                warp_point_handle = tween_callback.warp_point_handle
                warp_point = map.warp_points.at(warp_point_handle)
                warping_to_map_handle = warp_point.warp_to_map_handle
                warping_to_map = self.maps.at(warping_to_map_handle)
                unit.join_map(game, warping_to_map)
                if warping_to_map.is_town_map or warping_to_map_handle == 0:
                    # town maps or overworld can't get stuck as units dont check for
                    # collissions when pathing.
                    unit.set_spawn_point(
                        game, warp_point.warp_to_tile_point_move_grid)
                else:
                    # battle maps need a random spawn for now to avoid getting stuck
                    # on each other on top of the warp point when they re-enter the battle
                    # map.
                    unit.set_random_spawn_point(game)

                if unit.ai_state == UnitAIState.Selling:
                    if warping_to_map.handle == 0:
                        unit.move_to_town_warp_point(game)
                    elif warping_to_map.is_town_map:
                        unit.move_to_guild_building(game)
                elif unit.ai_state == UnitAIState.Battle:
                    if warping_to_map.handle == 0:
                        unit.move_to_battle_warp_point(game)
        elif tween_callback.tween_type == TweenType.UnitMoveToBuyAtMerchantShop:
            if tween_callback.is_final_point_in_path:
                unit = self.units.at(tween_callback.handle)
                map = self.maps.at(unit.map_handle)
                # basically a set delay
                tween_handle = game.world.get_handle(HandleType.TweenXY)
                tween = game.world.tween_xys.at(tween_handle)
                callback.tween_type = TweenType.UnitBuyingAtMerchantShop
                callback.handle = unit.handle
                callback.merchant_unit_handle = tween_callback.merchant_unit_handle
                duration = cast(2000, "Uint32")
                delay = cast(0, "Uint32")
                tween.set(game, unit.sprite.render_dst.dst, unit.sprite.render_dst.dst,
                          unit.sprite.render_dst.dst, False, 0.0, duration, delay, callback)
        elif tween_callback.tween_type == TweenType.UnitBuyingAtMerchantShop:
            unit = self.units.at(tween_callback.handle)
            merchant_unit = self.units.at(tween_callback.merchant_unit_handle)
            if not(merchant_unit.is_merchant()):
                print(
                    "TweenType.UnitBuyingAtMerchantShop. Merchant handle unit is not a merchant.")
                exit(1)
            # let other units shop at the merchant
            merchant_unit.unit_handle_buying_from_merchant = -1
            # have the merchant sell some items to the neutral unit
            merchant_unit.merchant_sell_to_unit(game)
            # unit can now go back to battle, Guild -> Shop -> Merchant Shop -> Battle
            unit.ai_state = UnitAIState.Battle
            unit.move_to_overworld_warp_point(game)
        elif tween_callback.tween_type == TweenType.PerformAbility:
            map = self.maps.at(tween_callback.map_handle)
            ability_handle = tween_callback.handle
            ability = self.abilities.at(ability_handle)
            acting_unit_handle = tween_callback.acting_unit_handle
            acting_unit = self.units.at(acting_unit_handle)
            receiving_unit = self.units.at(
                tween_callback.receiving_unit_handle)
            # remove the ability handle from the map and release the handle
            find_and_remove_handle(map.ability_handles, ability_handle)
            self.release_handle(HandleType.Ability, ability_handle)
            # set attacked by faction to prevent ksing
            receiving_unit.attacked_by_guild_handle = acting_unit.guild_handle
            # apply damage if unit is not already dead - prevents items from dropping to multiple
            # units, only the unit that killed gets the items
            if not(receiving_unit.stats.hp.value_is_at_min()):
                receiving_unit.stats.hp.dec(ability.ability.stats.damage)
                receiving_unit.on_hit(game, acting_unit_handle)
                if receiving_unit.stats.hp.value_is_at_min():
                    # normal exp
                    exp = receiving_unit.stats.experience_drop * receiving_unit.stats.level
                    exp_as_uint64 = cast(exp, "Uint64")
                    acting_unit.stats.experience.inc(exp_as_uint64)
                    if acting_unit.stats.experience.value_is_at_max():
                        # max level is 99, I am not wrapping exp to the next level, seems
                        # to have a lot of problems and I don't think it matters.
                        if acting_unit.stats.level < 99:
                            acting_unit.available_stat_points += get_stat_points_for_level(
                                acting_unit.stats.level)
                            acting_unit.stats.level += 1
                            acting_unit.stats.experience.set_to_min()
                            # double max exp to get to the next level
                            acting_unit.stats.experience.max *= 2
                    # job exp
                    job_exp = receiving_unit.stats.job_experience_drop * receiving_unit.stats.level
                    job_exp_as_uint64 = cast(job_exp, "Uint64")
                    acting_unit.stats.job_experience.inc(job_exp_as_uint64)
                    if acting_unit.stats.job_experience.value_is_at_max():
                        if acting_unit.stats.job_level < 10:
                            acting_unit.available_skill_points += 1
                            acting_unit.stats.job_level += 1
                            acting_unit.stats.job_experience.set_to_min()
                            acting_unit.stats.job_experience.max *= 2
                    receiving_unit.on_dead(game, acting_unit_handle)
                # damage text
                damage_text_handle = self.get_handle(HandleType.DamageText)
                damage_text = self.damage_texts.at(damage_text_handle)
                sprintf(damage_text.str, "%lu", ability.ability.stats.damage)
                damage_text_dst = create_point(
                    receiving_unit.sprite.render_dst.dst.x, receiving_unit.sprite.render_dst.dst.y)
                text_color = create_color(255, 255, 255, 255)
                text_outline_color = create_color(0, 0, 0, 255)
                damage_text.text_set_without_str(game,  damage_text_dst, FontStyle.Bold, TextAlignment.Left,
                                                 TextWordWrap.NoWrap, 500, 16, text_color, 1, text_outline_color, False)
                damage_text.render_dst.is_camera_rendered = True
                map.damage_text_handles.push_value(damage_text_handle)
                # damage text tween
                text_tween_handle = self.get_handle(HandleType.TweenXY)
                text_tween = self.tween_xys.at(text_tween_handle)
                start_rect = receiving_unit.sprite.render_dst.dst
                target_rect = start_rect
                target_rect.y -= 30
                duration = cast(2000, "Uint32")
                delay = cast(0, "Uint32")
                callback.tween_type = TweenType.DamageText
                callback.handle = damage_text_handle
                callback.receiving_unit_handle = tween_callback.receiving_unit_handle
                callback.map_handle = tween_callback.map_handle
                text_tween.set(game, start_rect, damage_text.render_dst.dst, target_rect,
                               False, 0.0, duration, delay, callback)
        elif tween_callback.tween_type == TweenType.ItemDrop:
            map = self.maps.at(tween_callback.map_handle)
            item_handle = tween_callback.handle
            item = self.items.at(item_handle)
            receiving_unit_handle = tween_callback.receiving_unit_handle
            receiving_unit = self.units.at(receiving_unit_handle)
            receiving_unit.inventory.add_item(game,
                                              item.item.item_name, item.quantity)
            find_and_remove_handle(map.item_handles, item_handle)
            self.release_handle(HandleType.Item, item_handle)
            if receiving_unit.ai_state != UnitAIState.Selling:
                receiving_unit.change_to_sell_item_ai_state(game)
        elif tween_callback.tween_type == TweenType.DamageText:
            # remove the damage text handle from the map and release the handle
            damage_text_handle = tween_callback.handle
            map = self.maps.at(tween_callback.map_handle)
            find_and_remove_handle(
                map.damage_text_handles, damage_text_handle)
            self.release_handle(HandleType.DamageText, damage_text_handle)

    def get_handle(self, handle_type: HandleType) -> int:
        if handle_type == HandleType.NA:
            print("World.get_handle. handle_type is NA.")
            exit(1)
            return -1
        elif handle_type == HandleType.Map:
            return self.maps.pool_get_handle(
                addr(self.maps_last_in_use_handle), "Maps")
        elif handle_type == HandleType.Building:
            return self.buildings.pool_get_handle(
                addr(self.buildings_last_in_use_handle), "Buildings")
        elif handle_type == HandleType.Unit:
            return self.units.pool_get_handle(
                addr(self.units_last_in_use_handle), "Units")
        elif handle_type == HandleType.Guild:
            return self.guilds.pool_get_handle(
                addr(self.guilds_last_in_use_handle), "Guilds")
        elif handle_type == HandleType.Item:
            return self.items.pool_get_handle(
                addr(self.items_last_in_use_handle), "Items")
        elif handle_type == HandleType.Ability:
            return self.abilities.pool_get_handle(
                addr(self.abilities_last_in_use_handle), "Abilities")
        elif handle_type == HandleType.TweenXY:
            return self.tween_xys.pool_get_handle(
                addr(self.tween_xys_last_in_use_handle), "TweenXYs")
        elif handle_type == HandleType.DamageText:
            return self.damage_texts.pool_get_handle(
                addr(self.damage_texts_last_in_use_handle), "DamgeTexts")

        print("World.get_handle. Unexpected point reached.")
        exit(1)
        return 0

    def release_handle(self, handle_type: HandleType, handle: int):
        # releases the handle
        # if the handle released is the last in use handle, then search
        # the array for the new last in use handle.
        if handle_type == HandleType.NA:
            print("World.release_handle. handle_type is NA.")
            exit(1)
            return
        elif handle_type == HandleType.Map:
            self.maps.pool_release_handle(
                handle, addr(self.maps_last_in_use_handle))
            return
        elif handle_type == HandleType.Building:
            self.buildings.pool_release_handle(
                handle, addr(self.buildings_last_in_use_handle))
            return
        elif handle_type == HandleType.Unit:
            self.units.pool_release_handle(
                handle, addr(self.units_last_in_use_handle))
            return
        elif handle_type == HandleType.Guild:
            self.guilds.pool_release_handle(
                handle, addr(self.guilds_last_in_use_handle))
            return
        elif handle_type == HandleType.Item:
            self.items.pool_release_handle(
                handle, addr(self.items_last_in_use_handle))
            return
        elif handle_type == HandleType.Ability:
            self.abilities.pool_release_handle(
                handle, addr(self.abilities_last_in_use_handle))
            return
        elif handle_type == HandleType.TweenXY:
            self.tween_xys.pool_release_handle(
                handle, addr(self.tween_xys_last_in_use_handle))
            return
        elif handle_type == HandleType.DamageText:
            self.damage_texts.pool_release_handle(
                handle, addr(self.damage_texts_last_in_use_handle))
            return

        print("World.release_handle. Unexpected point reached.")
        exit(1)
        return

    def create_initial_maps(self, game: Game):
        map_handle = self.get_handle(HandleType.Map)
        map = self.maps.at(map_handle)
        map.create_initial_overworld(game, 80, 80)

        map_handle = self.get_handle(HandleType.Map)
        map = self.maps.at(map_handle)
        map.create_initial(game, 40, 40, False)

        map_handle = self.get_handle(HandleType.Map)
        map = self.maps.at(map_handle)
        map.create_initial(game, 60, 60, True)

        building_handle = self.get_handle(HandleType.Building)
        building = self.buildings.at(building_handle)
        building_move_grid_tile_point = create_point(200, 200)
        building.set_to(game, BuildingName.TeleportationStone,
                        building_move_grid_tile_point)
        map.building_handles.push_value(building_handle)

        building_handle = self.get_handle(HandleType.Building)
        building = self.buildings.at(building_handle)
        building_move_grid_tile_point = create_point(0, 0)
        building.set_to(game, BuildingName.PlayerLeague,
                        building_move_grid_tile_point)
        map.building_handles.push_value(building_handle)

        building_handle = self.get_handle(HandleType.Building)
        building = self.buildings.at(building_handle)
        building_move_grid_tile_point = create_point(70, 0)
        building.set_to(game, BuildingName.Shop0,
                        building_move_grid_tile_point)
        map.building_handles.push_value(building_handle)

        building_handle = self.get_handle(HandleType.Building)
        building = self.buildings.at(building_handle)
        building_move_grid_tile_point = create_point(140, 0)
        building.set_to(game, BuildingName.RecruitmentCenter0,
                        building_move_grid_tile_point)
        map.building_handles.push_value(building_handle)

        map_handle = self.get_handle(HandleType.Map)
        map = self.maps.at(map_handle)
        map.create_initial(game, 40, 40, False)

    def create_initial_units(self, game: Game):
        for i in range(self.guilds.size):
            guild = self.guilds.at(i)
            if not(guild.in_use_in_pool):
                continue
            faction = Faction.Ally
            if i != 0:
                faction = Faction.Guild
            # add an explorer
            rand_map_handle = game.engine.get_rand_int(0, 1)
            if rand_map_handle == 0:
                map = self.maps.at(1)
            elif rand_map_handle == 1:
                map = self.maps.at(3)
            unit_handle = self.get_handle(HandleType.Unit)
            unit = self.units.at(unit_handle)
            unit.set_to(game, UnitName.Explorer, faction)
            unit.join_guild(game, guild)
            unit.join_map(game, map)
            unit.set_random_spawn_point(game)

            # add a merchant
            map = self.maps.at(2)
            unit_handle = self.get_handle(HandleType.Unit)
            unit = self.units.at(unit_handle)
            unit.set_to(game, UnitName.Merchant, faction)
            unit.join_guild(game, guild)
            unit.join_map(game, map)
            unit.set_random_spawn_point(game)

    def create_guilds(self, game: Game):
        # create a few guilds for now
        for i in range(8):
            guild_handle = self.get_handle(HandleType.Guild)
            guild = self.guilds.at(guild_handle)
            if i == 0:
                guild.set_to("Oceanside")
            elif i == 1:
                guild.set_to("Apparition")
            elif i == 2:
                guild.set_to("Lions")
            elif i == 3:
                guild.set_to("Thieves")
            elif i == 4:
                guild.set_to("Pisces Group")
            elif i == 5:
                guild.set_to("Telekinetics")
            elif i == 6:
                guild.set_to("Iron Sands")
            elif i == 7:
                guild.set_to("Psychic Allegiance")
        # create anonymouse guilds
        for i in range(10):
            guild_handle = self.get_handle(HandleType.Guild)
            guild = self.guilds.at(guild_handle)
            guild.is_anonymous = True
