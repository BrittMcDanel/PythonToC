from ct.src.engine import SDL_RenderCopy
from ct.src.image import *
from ct.src.input_events import InputEvents
from ct.src.utils import SDL_Rect, RenderDst, UIEvent, get_stat_cost, rect_contains_point, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import addr, Uint32, mod, UIRectPtr, rev_range, UISpritePtr, cast
from ct.src.constants import UIEventName, StatName, AIAbilityCondition, UnitsWindowTabName, UnitName, Faction, HandleType
from ct.src.input_events import InputEvents
from ct.src.ui_sprite import UISprite
from ct.src.text import TextLG, text_draw
from ct.src.ui_containers import GuildWindow, RecruitNoviceModal, TopNav, UIRenderable, UnitsWindow, MerchantsWindow
# weak imports
from ct.src.game import Game
from ct.src.unit import Unit


class UI:
    def __init__(self):
        self.renderables: Array[UIRenderable] = Array[UIRenderable](300)
        self.top_nav: TopNav = None
        self.recruit_novice_modal: RecruitNoviceModal = None
        self.guild_window: GuildWindow = None
        self.units_window: UnitsWindow = None
        self.merchants_window: MerchantsWindow = None
        self.is_mouse_over_ui: bool = None
        self.on_click_fired_this_frame: bool = None

    def init(self, game: Game):
        self.top_nav.init(game)
        self.recruit_novice_modal.init(game)
        self.guild_window.init(game)
        self.units_window.init(game)
        self.merchants_window.init(game)

    def clear(self):
        self.renderables.clear()

    def update(self, game: Game):
        # update all containers, the order they are updated in is the order they push
        # to the render buffer.
        self.top_nav.update(game)
        self.guild_window.update(game)
        self.units_window.update(game)
        self.merchants_window.update(game)
        self.recruit_novice_modal.update(game)

        # set these here instead of in clear as clear happens before all non-ui updates occur
        # and these updates need to know if the mouse is over the ui from the prev frame, if it
        # was set in clear it would always be false.
        self.is_mouse_over_ui = False
        self.on_click_fired_this_frame = False

        # update renderables, render buffer possibly contains items now
        for i in rev_range(self.renderables.size - 1, 0, 1):
            renderable = self.renderables.at(i)
            if renderable.text_lg != None:
                renderable.text_lg.text_update(game)
            elif renderable.sprite != None:
                renderable.sprite.update(game)
                if renderable.sprite.input_events.is_mouse_over:
                    self.is_mouse_over_ui = True
                # only allow one successful on click event per frame
                if not(self.on_click_fired_this_frame) and renderable.sprite.input_events.is_click:
                    self.on_click(game, renderable.sprite.ui_event)
                    if self.on_click_fired_this_frame:
                        self.after_on_click(game, renderable.sprite.ui_event)

    def draw(self, game: Game):
        for renderable in self.renderables:
            if renderable.sprite != None:
                renderable.sprite.draw(game)
            elif renderable.text_lg != None:
                renderable.text_lg.text_draw(game)
            elif renderable.regular_sprite.sprite != None:
                renderable.regular_sprite.sprite.draw_at(game,
                                                         renderable.regular_sprite.dst)
            elif renderable.unit_sprite.sprite != None:
                renderable.unit_sprite.sprite.draw_idle_at(
                    game, renderable.unit_sprite.dst)
            else:
                # if nothing else is set I assume you are rendering the unit, I don't want its
                # handle to be -1 as memset gaurantees 0, I think it is fine.
                unit = game.world.units.at(renderable.unit.handle)
                unit.draw_idle_at(game, renderable.unit.dst)

    def after_on_click(self, game: Game, ui_event: UIEvent):
        # handles things like closing dropdown menus, not primary on click things
        not_ai_dropdown = not(
            ui_event.event_name == UIEventName.UnitsWindowAISelect or ui_event.event_name == UIEventName.UnitsWindowAISelectBackground or ui_event.event_name == UIEventName.UnitsWindowAISelectOption)
        if game.world.ui.units_window.ai_ability_dropdown_visible and not_ai_dropdown:
            game.world.ui.units_window.ai_ability_dropdown_visible = False

    def on_click(self, game: Game, ui_event: UIEvent):
        # only set on_click_fired_this frame for events, NA is fine becuase it won't set it
        # and other renderables still have a chance to have on click fire. Setting it to true
        # here and if no events trigger it will be set back to False, just so you don't forget
        # to set it in any of these conditionals.
        self.on_click_fired_this_frame = True

        if ui_event.event_name == UIEventName.BuyRecruitModal:
            # prevent click on modal triggering a backdrop click
            return
        elif ui_event.event_name == UIEventName.BuyRecruitBackdrop:
            # modal backdrop clicked, hide the recruit novice modal
            self.recruit_novice_modal.set_visible(False)
        elif ui_event.event_name == UIEventName.BuyRecruitClose:
            # modal backdrop clicked, hide the recruit novice modal
            self.recruit_novice_modal.set_visible(False)
        elif ui_event.event_name == UIEventName.BuyExplorer:
            player_guild = game.world.guilds.at(0)
            # if player_guild.current_money < 500:
            #    return
            #player_guild.current_money -= 500
            self.recruit_novice_modal.set_visible(False)
            # add unit
            unit_handle = game.world.get_handle(HandleType.Unit)
            unit = game.world.units.at(unit_handle)
            unit.set_to(game, UnitName.Explorer, Faction.Ally)
            map = game.world.maps.at(1)
            unit.join_guild(game, player_guild)
            unit.join_map(game, map)
            unit.set_random_spawn_point(game)
        elif ui_event.event_name == UIEventName.BuyMerchant:
            player_guild = game.world.guilds.at(0)
            # if player_guild.current_money < 500:
            #    return
            #player_guild.current_money -= 500
            self.recruit_novice_modal.set_visible(False)
            # add unit
            unit_handle = game.world.get_handle(HandleType.Unit)
            unit = game.world.units.at(unit_handle)
            unit.set_to(game, UnitName.Merchant, Faction.Ally)
            map = game.world.maps.at(2)
            unit.join_guild(game, player_guild)
            unit.join_map(game, map)
            unit.set_random_spawn_point(game)
        elif ui_event.event_name == UIEventName.UnitsWindowOpen:
            # toggle visibility
            opposite_visible_state = not(game.world.ui.units_window.visible)
            game.world.ui.units_window.set_visible(opposite_visible_state)
        elif ui_event.event_name == UIEventName.UnitsWindowClose:
            game.world.ui.units_window.set_visible(False)
        elif ui_event.event_name == UIEventName.UnitsWindowBackground:
            # prevent click on modal triggering a backdrop click
            return
        elif ui_event.event_name == UIEventName.UnitsWindowSlot:
            handle = ui_event.handle
            guild_handle = ui_event.guild_handle
            guild = game.world.guilds.at(guild_handle)
            if handle <= guild.unit_handles.size - 1:
                game.world.ui.units_window.active_slot_idx = handle
        elif ui_event.event_name == UIEventName.UnitsWindowStatusTab:
            game.world.ui.units_window.active_tab = UnitsWindowTabName.Status
        elif ui_event.event_name == UIEventName.UnitsWindowInventoryTab:
            game.world.ui.units_window.active_tab = UnitsWindowTabName.Inventory
        elif ui_event.event_name == UIEventName.UnitsWindowAbilityTab:
            game.world.ui.units_window.active_tab = UnitsWindowTabName.Ability
        elif ui_event.event_name == UIEventName.UnitsWindowJobChangeTab:
            game.world.ui.units_window.active_tab = UnitsWindowTabName.JobChange
        elif ui_event.event_name == UIEventName.UnitsWindowAITab:
            game.world.ui.units_window.active_tab = UnitsWindowTabName.AI
        elif ui_event.event_name == UIEventName.UnitsWindowJobChange:
            guild_unit_idx = game.world.ui.units_window.active_slot_idx
            player_guild = game.world.guilds.at(0)
            unit_handle = player_guild.unit_handles[guild_unit_idx]
            unit = game.world.units.at(unit_handle)
            unit_name = ui_event.unit_name
            unit.set_to(game, unit_name, unit.faction)
        elif ui_event.event_name == UIEventName.UnitsWindowLearnAbility:
            guild_unit_idx = game.world.ui.units_window.active_slot_idx
            player_guild = game.world.guilds.at(0)
            unit_handle = player_guild.unit_handles[guild_unit_idx]
            unit = game.world.units.at(unit_handle)
            job_ability = unit.job_abilities.at(ui_event.handle)
            ability = unit.get_ability(job_ability.ability.ability_name)
            if unit.available_skill_points == 0:
                return
            if ability.skill_points < job_ability.ability.stats.max_skill_points:
                unit.available_skill_points -= 1
                ability.skill_points += 1
        elif ui_event.event_name == UIEventName.UnitsWindowIncreaseStats:
            guild_unit_idx = game.world.ui.units_window.active_slot_idx
            player_guild = game.world.guilds.at(0)
            unit_handle = player_guild.unit_handles[guild_unit_idx]
            unit = game.world.units.at(unit_handle)
            stat_name = ui_event.stat_name
            inc_val = cast(1, "Uint64")
            stat_cost = 0
            if stat_name == StatName.Strength:
                stat_cost = get_stat_cost(unit.stats.strength.value)
                if unit.available_stat_points >= stat_cost:
                    unit.available_stat_points -= stat_cost
                    unit.stats.strength.inc(inc_val)
            elif stat_name == StatName.Intelligence:
                stat_cost = get_stat_cost(unit.stats.intelligence.value)
                if unit.available_stat_points >= stat_cost:
                    unit.available_stat_points -= stat_cost
                    unit.stats.intelligence.inc(inc_val)
            elif stat_name == StatName.Dexterity:
                stat_cost = get_stat_cost(unit.stats.dexterity.value)
                if unit.available_stat_points >= stat_cost:
                    unit.available_stat_points -= stat_cost
                    unit.stats.dexterity.inc(inc_val)
            elif stat_name == StatName.Vitality:
                stat_cost = get_stat_cost(unit.stats.vitality.value)
                if unit.available_stat_points >= stat_cost:
                    unit.available_stat_points -= stat_cost
                    unit.stats.vitality.inc(inc_val)
            elif stat_name == StatName.Agility:
                stat_cost = get_stat_cost(unit.stats.agility.value)
                if unit.available_stat_points >= stat_cost:
                    unit.available_stat_points -= stat_cost
                    unit.stats.agility.inc(inc_val)
            elif stat_name == StatName.Luck:
                stat_cost = get_stat_cost(unit.stats.luck.value)
                if unit.available_stat_points >= stat_cost:
                    unit.available_stat_points -= stat_cost
                    unit.stats.luck.inc(inc_val)
        elif ui_event.event_name == UIEventName.UnitsWindowAISelect:
            if game.world.ui.units_window.ai_ability_dropdown_visible and game.world.ui.units_window.ai_ability_active_idx == ui_event.handle:
                game.world.ui.units_window.ai_ability_dropdown_visible = False
            else:
                game.world.ui.units_window.ai_ability_dropdown_visible = True
                game.world.ui.units_window.ai_ability_active_idx = ui_event.handle
        elif ui_event.event_name == UIEventName.UnitsWindowAISelectOption:
            guild_unit_idx = game.world.ui.units_window.active_slot_idx
            player_guild = game.world.guilds.at(0)
            unit_handle = player_guild.unit_handles[guild_unit_idx]
            unit = game.world.units.at(unit_handle)
            ability_handle = ui_event.handle
            # delete button, clear ai slot
            if ability_handle == game.world.ui.units_window.ai_ability_dropdown_options.size - 1:
                ai_ability_handle = game.world.ui.units_window.ai_ability_active_idx
                ai_ability = unit.ai_abilities.at(ai_ability_handle)
                ai_ability.clear()
                game.world.ui.units_window.ai_ability_dropdown_visible = False
            elif ability_handle <= unit.abilities.size - 1:
                ability = unit.abilities.at(ability_handle)
                ai_ability_handle = game.world.ui.units_window.ai_ability_active_idx
                ai_ability = unit.ai_abilities.at(ai_ability_handle)
                ai_ability.set(ability_handle, AIAbilityCondition.Always)
                game.world.ui.units_window.ai_ability_dropdown_visible = False
        elif ui_event.event_name == UIEventName.UnitsWindowAISelectBackground:
            return
        elif ui_event.event_name == UIEventName.MerchantsWindowOpen:
            # toggle visibility
            opposite_visible_state = not(
                game.world.ui.merchants_window.visible)
            game.world.ui.merchants_window.set_visible(opposite_visible_state)
        elif ui_event.event_name == UIEventName.MerchantsWindowClose:
            game.world.ui.merchants_window.set_visible(False)
        elif ui_event.event_name == UIEventName.MerchantsWindowBackground:
            # prevent click on modal triggering a backdrop click
            return
        elif ui_event.event_name == UIEventName.MerchantsWindowSlot:
            handle = ui_event.handle
            guild_handle = ui_event.guild_handle
            guild = game.world.guilds.at(guild_handle)
            if handle <= guild.merchant_handles.size - 1:
                game.world.ui.merchants_window.active_slot_idx = handle
        elif ui_event.event_name == UIEventName.GuildWindowOpen:
            # toggle visibility
            opposite_visible_state = not(
                game.world.ui.guild_window.visible)
            game.world.ui.guild_window.set_visible(opposite_visible_state)
        elif ui_event.event_name == UIEventName.GuildWindowClose:
            game.world.ui.guild_window.set_visible(False)
        elif ui_event.event_name == UIEventName.GuildWindowBackground:
            # prevent click on modal triggering a backdrop click
            return
        else:
            self.on_click_fired_this_frame = False
