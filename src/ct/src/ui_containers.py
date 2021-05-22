from ct.src.engine import SDL_RenderCopy
from ct.src.utils import SDL_Rect, RenderDst, create_point, create_rect, create_color, get_stat_cost, get_unit_name_job_tier, set_scaled_rect, set_scaled_rect_with_camera, unit_can_job_change
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import N, addr, Uint32, cast, array_capacity, deref, mod, TextLGPtr, UISpritePtr, SpritePtr, UnitSpritePtr, sprintf
from ct.src.ui_sprite import UISprite
from ct.src.text import TextLG
from ct.src.sprite import Sprite
from ct.src.constants import ImageName, StatName, UIEventName, FontStyle, TextAlignment, TextWordWrap, UnitName, UnitsWindowTabName
from ct.src.unit_sprite import UnitSprite
# weak imports
from ct.src.game import Game


class UIUnitRender:
    def __init__(self):
        self.handle: int = None
        self.dst: SDL_Rect = None


class UnitSpriteRender:
    def __init__(self):
        self.sprite: UnitSpritePtr = None
        self.dst: SDL_Rect = None


class SpriteRender:
    def __init__(self):
        self.sprite: SpritePtr = None
        self.dst: SDL_Rect = None


class UIRenderable:
    def __init__(self):
        self.sprite: UISpritePtr = None
        self.text_lg: TextLGPtr = None
        self.regular_sprite: SpriteRender = None
        self.unit_sprite: UnitSpriteRender = N
        self.unit: UIUnitRender = None

    def set_sprite(self, game: Game, sprite: UISprite):
        self.clear()
        self.sprite = sprite
        game.world.ui.renderables.push(self)

    def set_text_lg(self, game: Game, text_lg: TextLG):
        self.clear()
        self.text_lg = text_lg
        game.world.ui.renderables.push(self)

    def set_unit(self, game: Game, unit_handle: int, dst: SDL_Rect):
        self.clear()
        self.unit.handle = unit_handle
        self.unit.dst = deref(dst)
        game.world.ui.renderables.push(self)

    def set_regular_sprite(self, game: Game,  sprite: Sprite, dst: SDL_Rect):
        self.clear()
        self.regular_sprite.sprite = sprite
        self.regular_sprite.dst = deref(dst)
        game.world.ui.renderables.push(self)

    def set_unit_sprite(self, game: Game,  sprite: UnitSprite, dst: SDL_Rect):
        self.clear()
        self.unit_sprite.sprite = sprite
        self.unit_sprite.dst = deref(dst)
        game.world.ui.renderables.push(self)

    def clear(self):
        # there is a compiler bug where class functions can't match
        # non-class function names. clear is already defined for arrays.
        # will fix this later probably.
        self.sprite = None
        self.text_lg = None
        self.regular_sprite.sprite = None
        self.unit_sprite.sprite = None
        self.unit.handle = 0


class TopNav:
    def __init__(self):
        self.background: UISprite = None
        self.league_text: TextLG = None
        self.money_text: TextLG = None
        self.guild_button: UISprite = None
        self.units_button: UISprite = None
        self.merchants_button: UISprite = None
        self.visible: bool = None

    def init(self, game: Game):
        # top nav is initially (always?) visible
        self.visible = True
        self.background.render_dst.is_camera_rendered = False
        self.background.anim_speed = 100
        background_src = create_rect(0, 240, 80, 40)
        self.background.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, background_src)
        self.guild_button.render_dst.is_camera_rendered = False
        self.guild_button.anim_speed = 100
        self.guild_button.ui_event.event_name = UIEventName.GuildWindowOpen
        guild_button_src = create_rect(48, 288, 24, 24)
        self.guild_button.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, guild_button_src)
        self.units_button.render_dst.is_camera_rendered = False
        self.units_button.anim_speed = 100
        self.units_button.ui_event.event_name = UIEventName.UnitsWindowOpen
        units_button_src = create_rect(0, 288, 24, 24)
        self.units_button.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, units_button_src)
        self.merchants_button.render_dst.is_camera_rendered = False
        self.merchants_button.anim_speed = 100
        self.merchants_button.ui_event.event_name = UIEventName.MerchantsWindowOpen
        merchants_button_src = create_rect(24, 288, 24, 24)
        self.merchants_button.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, merchants_button_src)

        text_color = create_color(255, 255, 255, 255)
        text_outline_color = create_color(0, 0, 0, 255)
        text_dst = create_point(0, 0)
        self.league_text.text_set(game, "Muny", text_dst, FontStyle.Bold, TextAlignment.Left,
                                  TextWordWrap.NoWrap, 500, 12, text_color, 1, text_outline_color, False)
        text_color = create_color(0, 0, 0, 255)
        text_outline_color = create_color(0, 0, 0, 255)
        text_dst = create_point(0, 0)
        self.money_text.text_set(game, "Muny", text_dst, FontStyle.Bold, TextAlignment.Left,
                                 TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)

    def set_visible(self, visible: bool):
        self.visible = visible

    def update(self, game: Game):
        if not(self.visible):
            return
        player_guild = game.world.guilds.at(0)
        self.league_text.str.string_set(player_guild.display_name)
        sprintf(self.money_text.str, "%lu Muny", player_guild.current_money)

        background_dst = self.background.render_dst.dst
        self.league_text.render_dst.dst.x = background_dst.x + 2
        self.league_text.render_dst.dst.y = background_dst.y + 2
        self.money_text.render_dst.dst.x = background_dst.x + 4
        self.money_text.render_dst.dst.y = background_dst.y + 21
        self.guild_button.render_dst.dst.x = background_dst.x + 2
        self.guild_button.render_dst.dst.y = background_dst.y + 44
        self.units_button.render_dst.dst = self.guild_button.render_dst.dst
        self.units_button.render_dst.dst.x += 26
        self.merchants_button.render_dst.dst = self.units_button.render_dst.dst
        self.merchants_button.render_dst.dst.x += 26
        renderable = UIRenderable()
        renderable.set_sprite(game, self.background)
        renderable.set_text_lg(game, self.league_text)
        renderable.set_text_lg(game, self.money_text)
        renderable.set_sprite(game, self.guild_button)
        renderable.set_sprite(game, self.units_button)
        renderable.set_sprite(game, self.merchants_button)


class RecruitNoviceModal:
    def __init__(self):
        self.backdrop: UISprite = None
        self.background: UISprite = None
        self.close_button: UISprite = None
        self.header_text: TextLG = None
        self.unit_slots_ok_buttons: Array[UISprite] = Array[UISprite](2)
        self.unit_slots_ok_button_texts: Array[TextLG] = Array[TextLG](2)
        self.unit_header_texts: Array[TextLG] = Array[TextLG](2)
        self.unit_cost_texts: Array[TextLG] = Array[TextLG](2)
        self.visible: bool = None

    def init(self, game: Game):
        self.backdrop.render_dst.is_camera_rendered = False
        self.backdrop.anim_speed = 100
        self.backdrop.ui_event.event_name = UIEventName.BuyRecruitBackdrop
        backdrop_src = create_rect(0, 1688, 640, 360)
        self.backdrop.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, backdrop_src)
        self.background.render_dst.is_camera_rendered = False
        self.background.anim_speed = 100
        self.background.ui_event.event_name = UIEventName.BuyRecruitModal
        background_src = create_rect(0, 32, 180, 165)
        self.background.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, background_src)
        self.close_button.render_dst.is_camera_rendered = False
        self.close_button.anim_speed = 100
        self.close_button.ui_event.event_name = UIEventName.BuyRecruitClose
        close_button_src = create_rect(0, 1664, 10, 10)
        self.close_button.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, close_button_src)
        # unit slots
        self.unit_header_texts.size = array_capacity(
            self.unit_header_texts)
        self.unit_cost_texts.size = array_capacity(
            self.unit_cost_texts)
        self.unit_slots_ok_buttons.size = array_capacity(
            self.unit_slots_ok_buttons)
        self.unit_slots_ok_button_texts.size = array_capacity(
            self.unit_slots_ok_button_texts)
        for i in range(self.unit_slots_ok_buttons.size):
            ok_button = self.unit_slots_ok_buttons.at(i)
            if i == 0:
                ok_button.ui_event.event_name = UIEventName.BuyExplorer
            elif i == 1:
                ok_button.ui_event.event_name = UIEventName.BuyMerchant
            ok_button.render_dst.is_camera_rendered = False
            ok_button.anim_speed = 100
            src = create_rect(60, 0, 60, 24)
            ok_button.shared_srcs = game.sprite_db.find(
                game, ImageName.UI, src)
            ok_button_text = self.unit_slots_ok_button_texts.at(i)
            text_color = create_color(255, 255, 255, 255)
            text_outline_color = create_color(0, 0, 0, 255)
            text_dst = create_point(0, 0)
            ok_button_text.text_set(game, "Recruit", text_dst, FontStyle.Bold, TextAlignment.Left,
                                    TextWordWrap.NoWrap, 500, 12, text_color, 1, text_outline_color, False)
            unit_header_text = self.unit_header_texts.at(i)
            text_color = create_color(0, 0, 0, 255)
            unit_header_str = "Explorer"
            if i == 1:
                unit_header_str = "Merchant"
            unit_header_text.text_set(game, unit_header_str, text_dst, FontStyle.Bold, TextAlignment.Left,
                                      TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
            unit_cost_text = self.unit_cost_texts.at(i)
            unit_cost_text.text_set(game, "500 Muny", text_dst, FontStyle.Bold, TextAlignment.Left,
                                    TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)

        text_color = create_color(0, 0, 0, 255)
        text_outline_color = create_color(0, 0, 0, 255)
        text_dst = create_point(0, 0)
        self.header_text.text_set(game, "Recruit new unit", text_dst, FontStyle.Bold, TextAlignment.Left,
                                  TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)

    def set_visible(self, visible: bool):
        self.visible = visible
        # clear any input state if the container is hidden
        if not(self.visible):
            self.backdrop.input_events.clear()
            self.backdrop.input_events.clear()
            self.close_button.input_events.clear()
            for i in range(self.unit_slots_ok_buttons.size):
                ok_button = self.unit_slots_ok_buttons.at(i)
                ok_button.input_events.clear()

    def update(self, game: Game):
        if not(self.visible):
            return
        self.backdrop.render_dst.dst.x = 0
        self.backdrop.render_dst.dst.y = 0
        self.background.render_dst.dst.x = 640 / 2 - 180 / 2
        self.background.render_dst.dst.y = 360 / 2 - 200 / 2
        self.header_text.render_dst.dst = self.background.render_dst.dst
        self.header_text.render_dst.dst.x += 5
        self.header_text.render_dst.dst.y += 12
        self.close_button.render_dst.dst = self.background.render_dst.dst
        self.close_button.render_dst.dst.x += 162
        self.close_button.render_dst.dst.y += 10
        renderable = UIRenderable()
        renderable.set_sprite(game, self.backdrop)
        renderable.set_sprite(game, self.background)
        renderable.set_sprite(game, self.close_button)
        renderable.set_text_lg(game, self.header_text)
        for i in range(self.unit_slots_ok_buttons.size):
            unit_name = UnitName.Explorer
            if i == 1:
                unit_name = UnitName.Merchant
            unit = game.unit_db.get_unit(unit_name)
            unit_dst = self.background.render_dst.dst
            unit_dst.x += 34 + (i * 90)
            unit_dst.y += 80
            renderable.set_unit_sprite(game, unit.sprite, unit_dst)

            unit_header_text = self.unit_header_texts.at(i)
            unit_header_text.render_dst.dst = unit_dst
            unit_header_text.render_dst.dst.x -= 10
            unit_header_text.render_dst.dst.y -= 35
            unit_cost_text = self.unit_cost_texts.at(i)
            unit_cost_text.render_dst.dst = unit_header_text.render_dst.dst
            unit_cost_text.render_dst.dst.y += 12
            ok_button = self.unit_slots_ok_buttons.at(i)
            ok_button.render_dst.dst = unit_dst
            ok_button.render_dst.dst.x -= 20
            ok_button.render_dst.dst.y += 45
            ok_button_text = self.unit_slots_ok_button_texts.at(i)
            ok_button_text.render_dst.dst = ok_button.render_dst.dst
            ok_button_text.render_dst.dst.x += 12
            ok_button_text.render_dst.dst.y += 6

            renderable.set_text_lg(game, unit_header_text)
            renderable.set_text_lg(game, unit_cost_text)
            renderable.set_sprite(game, ok_button)
            renderable.set_text_lg(game, ok_button_text)


class UnitsWindow:
    def __init__(self):
        self.background: UISprite = None
        self.window_text: TextLG = None
        self.window_close_button: UISprite = None
        self.unit_slots: Array[UISprite] = Array[UISprite](30)
        self.status_tab: UISprite = None
        self.inventory_tab: UISprite = None
        self.ability_tab: UISprite = None
        self.job_change_tab: UISprite = None
        self.ai_tab: UISprite = None
        self.status_tab_text: TextLG = None
        self.inventory_tab_text: TextLG = None
        self.ability_tab_text: TextLG = None
        self.job_change_tab_text: TextLG = None
        self.ai_tab_text: TextLG = None
        self.job_text: TextLG = None
        self.level_text: TextLG = None
        self.job_level_text: TextLG = None
        self.experience_text: TextLG = None
        self.job_experience_text: TextLG = None
        self.strength_text: TextLG = None
        self.intelligence_text: TextLG = None
        self.dexterity_text: TextLG = None
        self.vitality_text: TextLG = None
        self.agility_text: TextLG = None
        self.luck_text: TextLG = None
        self.available_stat_points_text: TextLG = None
        self.increase_stat_buttons: Array[UISprite] = Array[UISprite](6)
        self.increase_stat_icons: Array[UISprite] = Array[UISprite](6)
        self.increase_stat_cost_texts: Array[TextLG] = Array[TextLG](6)
        self.inventory_slots: Array[UISprite] = Array[UISprite](50)
        self.inventory_quantity_texts: Array[TextLG] = Array[TextLG](50)
        self.available_skill_points_text: TextLG = None
        self.ability_slots: Array[UISprite] = Array[UISprite](10)
        self.ability_skill_point_texts: Array[TextLG] = Array[TextLG](10)
        self.job_change_row_2_slots: Array[UISprite] = Array[Sprite](5)
        self.job_change_row_3_slots: Array[UISprite] = Array[Sprite](10)
        self.next_job_change_level_text: TextLG = None
        self.ai_ability_slots: Array[UISprite] = Array[UISprite](12)
        self.ai_ability_slot_order_texts: Array[TextLG] = Array[TextLG](12)
        self.ai_ability_dropdown_background: UISprite = None
        self.ai_ability_dropdown_options: Array[UISprite] = Array[UISprite](9)
        self.ai_ability_remove_icon: UISprite = None
        self.active_tab: UnitsWindowTabName = None
        self.active_slot_idx: int = None
        self.ai_ability_dropdown_visible: bool = None
        self.ai_ability_active_idx: int = None
        self.visible: bool = None

    def init(self, game: Game):
        self.active_tab = UnitsWindowTabName.Status
        # unit slots needs to have the same capacity as guild.unit_handles
        self.background.render_dst.is_camera_rendered = False
        self.background.anim_speed = 100
        self.background.ui_event.event_name = UIEventName.UnitsWindowBackground
        background_src = create_rect(640, 1786, 544, 262)
        self.background.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, background_src)
        self.window_close_button.render_dst.is_camera_rendered = False
        self.window_close_button.anim_speed = 100
        self.window_close_button.ui_event.event_name = UIEventName.UnitsWindowClose
        close_button_src = create_rect(10, 1664, 10, 10)
        self.window_close_button.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, close_button_src)
        self.status_tab.render_dst.is_camera_rendered = False
        self.status_tab.anim_speed = 100
        self.status_tab.ui_event.event_name = UIEventName.UnitsWindowStatusTab
        tab_src = create_rect(0, 364, 64, 25)
        self.status_tab.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, tab_src)
        self.inventory_tab.render_dst.is_camera_rendered = False
        self.inventory_tab.anim_speed = 100
        self.inventory_tab.ui_event.event_name = UIEventName.UnitsWindowInventoryTab
        tab_src = create_rect(0, 364, 64, 25)
        self.inventory_tab.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, tab_src)
        self.ability_tab.render_dst.is_camera_rendered = False
        self.ability_tab.anim_speed = 100
        self.ability_tab.ui_event.event_name = UIEventName.UnitsWindowAbilityTab
        tab_src = create_rect(0, 364, 64, 25)
        self.ability_tab.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, tab_src)
        self.job_change_tab.render_dst.is_camera_rendered = False
        self.job_change_tab.anim_speed = 100
        self.job_change_tab.ui_event.event_name = UIEventName.UnitsWindowJobChangeTab
        tab_src = create_rect(0, 364, 64, 25)
        self.job_change_tab.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, tab_src)
        self.ai_tab.render_dst.is_camera_rendered = False
        self.ai_tab.anim_speed = 100
        self.ai_tab.ui_event.event_name = UIEventName.UnitsWindowAITab
        tab_src = create_rect(0, 364, 64, 25)
        self.ai_tab.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, tab_src)
        self.ai_ability_dropdown_background.render_dst.is_camera_rendered = False
        self.ai_ability_dropdown_background.anim_speed = 100
        src = create_rect(0, 431, 80, 80)
        self.ai_ability_dropdown_background.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, src)
        self.ai_ability_dropdown_background.ui_event.event_name = UIEventName.UnitsWindowAISelectBackground
        self.ai_ability_remove_icon.render_dst.is_camera_rendered = False
        self.ai_ability_remove_icon.anim_speed = 100
        src = create_rect(20, 40, 20, 20)
        self.ai_ability_remove_icon.shared_srcs = game.sprite_db.find(
            game, ImageName.Items, src)

        text_color = create_color(255, 255, 255, 255)
        text_outline_color = create_color(0, 0, 0, 255)
        text_dst = create_point(0, 0)
        self.window_text.text_set(game, "Units", text_dst, FontStyle.Bold, TextAlignment.Left,
                                  TextWordWrap.NoWrap, 500, 12, text_color, 1, text_outline_color, False)

        text_color = create_color(0, 0, 0, 255)
        text_outline_color = create_color(0, 0, 0, 255)
        text_dst = create_point(0, 0)
        self.status_tab_text.text_set(game, "Status", text_dst, FontStyle.Bold, TextAlignment.Left,
                                      TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.inventory_tab_text.text_set(game, "Inventory", text_dst, FontStyle.Bold, TextAlignment.Left,
                                         TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.ability_tab_text.text_set(game, "Ability", text_dst, FontStyle.Bold, TextAlignment.Left,
                                       TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.job_change_tab_text.text_set(game, "Job", text_dst, FontStyle.Bold, TextAlignment.Left,
                                          TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.ai_tab_text.text_set(game, "AI", text_dst, FontStyle.Bold, TextAlignment.Left,
                                  TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)

        self.job_text.text_set(game, "Job name", text_dst, FontStyle.Bold, TextAlignment.Left,
                               TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.level_text.text_set(game, "Level", text_dst, FontStyle.Bold, TextAlignment.Left,
                                 TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.job_level_text.text_set(game, "Level", text_dst, FontStyle.Bold, TextAlignment.Left,
                                     TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.experience_text.text_set(game, "Experience", text_dst, FontStyle.Bold, TextAlignment.Left,
                                      TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.job_experience_text.text_set(game, "Experience", text_dst, FontStyle.Bold, TextAlignment.Left,
                                          TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.strength_text.text_set(game, "Strength:", text_dst, FontStyle.Bold, TextAlignment.Left,
                                    TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.intelligence_text.text_set(game, "Intelligence:", text_dst, FontStyle.Bold, TextAlignment.Left,
                                        TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.dexterity_text.text_set(game, "Dexterity:", text_dst, FontStyle.Bold, TextAlignment.Left,
                                     TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.vitality_text.text_set(game, "Vitality:", text_dst, FontStyle.Bold, TextAlignment.Left,
                                    TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.agility_text.text_set(game, "Agility:", text_dst, FontStyle.Bold, TextAlignment.Left,
                                   TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.luck_text.text_set(game, "Luck:", text_dst, FontStyle.Bold, TextAlignment.Left,
                                TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.next_job_change_level_text.text_set(game, "Next Job Change", text_dst, FontStyle.Bold, TextAlignment.Left,
                                                 TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.available_stat_points_text.text_set(game, "Stat Points", text_dst, FontStyle.Bold, TextAlignment.Left,
                                                 TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)
        self.available_skill_points_text.text_set(game, "Skill points", text_dst, FontStyle.Bold, TextAlignment.Left,
                                                  TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)

        # increase stat buttons
        increase_stat_button_src = create_rect(0, 413, 13, 12)
        stat_icon_src = create_rect(0, 425, 9, 6)
        self.increase_stat_buttons.size = array_capacity(
            self.increase_stat_buttons)
        self.increase_stat_icons.size = array_capacity(
            self.increase_stat_icons)
        self.increase_stat_cost_texts.size = array_capacity(
            self.increase_stat_cost_texts)
        for i, stat_button in enumerate(self.increase_stat_buttons):
            stat_enum_value = cast(i + 1, "StatName")
            stat_icon = self.increase_stat_icons.at(i)
            stat_cost_text = self.increase_stat_cost_texts.at(i)
            stat_button.render_dst.is_camera_rendered = False
            stat_button.anim_speed = 100
            stat_button.ui_event.event_name = UIEventName.UnitsWindowIncreaseStats
            stat_button.ui_event.stat_name = stat_enum_value
            stat_button.shared_srcs = game.sprite_db.find(
                game, ImageName.UI, increase_stat_button_src)
            stat_icon.render_dst.is_camera_rendered = False
            stat_icon.anim_speed = 100
            stat_icon.shared_srcs = game.sprite_db.find(
                game, ImageName.UI, stat_icon_src)
            stat_cost_text.text_set(game, "1", text_dst, FontStyle.Bold, TextAlignment.Left,
                                    TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)

        # set units slots size
        self.unit_slots.size = array_capacity(self.unit_slots)
        for i in range(self.unit_slots.size):
            unit_slot = self.unit_slots.at(i)
            unit_slot.render_dst.is_camera_rendered = False
            unit_slot.anim_speed = 100
            unit_slot.ui_event.event_name = UIEventName.UnitsWindowSlot
            unit_slot.ui_event.handle = i
            # always showing the player's guild for now
            unit_slot.ui_event.guild_handle = 0
            slot_src = create_rect(0, 320, 24, 44)
            unit_slot.shared_srcs = game.sprite_db.find(
                game, ImageName.UI, slot_src)

        # set inventory slots size
        self.inventory_slots.size = array_capacity(self.inventory_slots)
        self.inventory_quantity_texts.size = array_capacity(
            self.inventory_quantity_texts)
        if self.inventory_slots.size != self.inventory_quantity_texts.size:
            print(
                "ui_containers. UnitsWindow - inventory slots size != inventory quantity texts size.")
            exit(1)
        for i in range(self.inventory_slots.size):
            inventory_slot = self.inventory_slots.at(i)
            inventory_slot.render_dst.is_camera_rendered = False
            inventory_slot.anim_speed = 100
            slot_src = create_rect(0, 389, 24, 24)
            inventory_slot.shared_srcs = game.sprite_db.find(
                game, ImageName.UI, slot_src)

            text_color = create_color(0, 0, 0, 255)
            text_outline_color = create_color(255, 255, 255, 255)
            text_dst = create_point(0, 0)
            inventory_quantity_text = self.inventory_quantity_texts.at(i)
            inventory_quantity_text.text_set(game, "0", text_dst, FontStyle.Bold, TextAlignment.Left,
                                             TextWordWrap.NoWrap, 500, 12, text_color, 1, text_outline_color, False)

        # ability slots
        self.ability_slots.size = array_capacity(self.ability_slots)
        self.ability_skill_point_texts.size = array_capacity(
            self.ability_skill_point_texts)
        for i in range(self.ability_slots.size):
            ability_slot = self.ability_slots.at(i)
            ability_slot.ui_event.event_name = UIEventName.UnitsWindowLearnAbility
            ability_slot.ui_event.handle = i
            ability_slot.render_dst.is_camera_rendered = False
            ability_slot.anim_speed = 100
            slot_src = create_rect(0, 389, 24, 24)
            ability_slot.shared_srcs = game.sprite_db.find(
                game, ImageName.UI, slot_src)

            text_color = create_color(0, 0, 0, 255)
            text_outline_color = create_color(255, 255, 255, 255)
            text_dst = create_point(0, 0)
            ability_skill_point_text = self.ability_skill_point_texts.at(i)
            ability_skill_point_text.text_set(game, "0", text_dst, FontStyle.Bold, TextAlignment.Left,
                                              TextWordWrap.NoWrap, 500, 12, text_color, 1, text_outline_color, False)

        # job change slots
        self.job_change_row_2_slots.size = array_capacity(
            self.job_change_row_2_slots)
        self.job_change_row_3_slots.size = array_capacity(
            self.job_change_row_3_slots)
        for i, slot in enumerate(self.job_change_row_2_slots):
            slot.render_dst.is_camera_rendered = False
            slot.anim_speed = 100
            slot_src = create_rect(0, 320, 24, 44)
            slot.shared_srcs = game.sprite_db.find(
                game, ImageName.UI, slot_src)
            slot.ui_event.event_name = UIEventName.UnitsWindowJobChange
            if i == 0:
                slot.ui_event.unit_name = UnitName.Mage
            else:
                slot.ui_event.unit_name = UnitName.Explorer
        for i, slot in enumerate(self.job_change_row_3_slots):
            slot.render_dst.is_camera_rendered = False
            slot.anim_speed = 100
            slot_src = create_rect(0, 320, 24, 44)
            slot.shared_srcs = game.sprite_db.find(
                game, ImageName.UI, slot_src)
            slot.ui_event.event_name = UIEventName.UnitsWindowJobChange
            if i == 0:
                slot.ui_event.unit_name = UnitName.Wizard
            elif i == 1:
                slot.ui_event.unit_name = UnitName.Scholar
            else:
                slot.ui_event.unit_name = UnitName.Explorer

        # ai
        self.ai_ability_slots.size = array_capacity(self.ai_ability_slots)
        self.ai_ability_slot_order_texts.size = array_capacity(
            self.ai_ability_slot_order_texts)
        self.ai_ability_dropdown_options.size = array_capacity(
            self.ai_ability_dropdown_options)
        for i, slot in enumerate(self.ai_ability_slots):
            slot.render_dst.is_camera_rendered = False
            slot.anim_speed = 100
            slot_src = create_rect(0, 389, 24, 24)
            slot.shared_srcs = game.sprite_db.find(
                game, ImageName.UI, slot_src)
            slot.ui_event.event_name = UIEventName.UnitsWindowAISelect
            slot.ui_event.handle = i
            ability_order_text = self.ai_ability_slot_order_texts.at(i)
            ability_order_text.text_set(game, "0", text_dst, FontStyle.Bold, TextAlignment.Left,
                                        TextWordWrap.NoWrap, 500, 12, text_color, 1, text_outline_color, False)
        for i, slot in enumerate(self.ai_ability_dropdown_options):
            slot.render_dst.is_camera_rendered = False
            slot.anim_speed = 100
            slot_src = create_rect(0, 389, 24, 24)
            slot.shared_srcs = game.sprite_db.find(
                game, ImageName.UI, slot_src)
            slot.ui_event.event_name = UIEventName.UnitsWindowAISelectOption
            slot.ui_event.handle = i

    def set_visible(self, visible: bool):
        self.visible = visible
        if not(self.visible):
            self.background.input_events.clear()

    def update(self, game: Game):
        if not(self.visible):
            return
        self.background.render_dst.dst.x = 0
        self.background.render_dst.dst.y = 0
        background_src = self.background.shared_srcs.srcs.at(0)
        base_res_w = game.engine.base_resolution.x
        base_res_h = game.engine.base_resolution.y
        self.background.render_dst.dst.x = base_res_w / 2 - background_src.w / 2
        self.background.render_dst.dst.y = base_res_h / 2 - background_src.h / 2
        background_dst = self.background.render_dst.dst
        self.window_text.render_dst.dst = background_dst
        self.window_text.render_dst.dst.x += 4
        self.window_text.render_dst.dst.y += 6
        self.window_close_button.render_dst.dst = background_dst
        self.window_close_button.render_dst.dst.x += background_src.w - 15
        self.window_close_button.render_dst.dst.y += 6
        slot_dst = background_dst
        slot_dst.x += 6
        slot_dst.y += 24 + 6
        start_slot_dst = slot_dst
        slot_inc = create_point(25, 45)
        slot_padding = 2
        cols = 6
        wrap_at_idx = cols - 1

        # background
        renderable = UIRenderable()
        renderable.set_sprite(game, self.background)
        renderable.set_text_lg(game, self.window_text)
        renderable.set_sprite(game, self.window_close_button)

        # tabs
        self.status_tab.render_dst.dst = background_dst
        self.status_tab.render_dst.dst.x += 168
        self.status_tab.render_dst.dst.y += 28
        self.inventory_tab.render_dst.dst = self.status_tab.render_dst.dst
        self.inventory_tab.render_dst.dst.x += 66
        self.ability_tab.render_dst.dst = self.inventory_tab.render_dst.dst
        self.ability_tab.render_dst.dst.x += 66
        self.job_change_tab.render_dst.dst = self.ability_tab.render_dst.dst
        self.job_change_tab.render_dst.dst.x += 66
        self.ai_tab.render_dst.dst = self.job_change_tab.render_dst.dst
        self.ai_tab.render_dst.dst.x += 66
        self.status_tab_text.render_dst.dst = self.status_tab.render_dst.dst
        self.status_tab_text.render_dst.dst.x += 4
        self.status_tab_text.render_dst.dst.y += 6
        self.inventory_tab_text.render_dst.dst = self.inventory_tab.render_dst.dst
        self.inventory_tab_text.render_dst.dst.x += 4
        self.inventory_tab_text.render_dst.dst.y += 6
        self.ability_tab_text.render_dst.dst = self.ability_tab.render_dst.dst
        self.ability_tab_text.render_dst.dst.x += 4
        self.ability_tab_text.render_dst.dst.y += 6
        self.job_change_tab_text.render_dst.dst = self.job_change_tab.render_dst.dst
        self.job_change_tab_text.render_dst.dst.x += 4
        self.job_change_tab_text.render_dst.dst.y += 6
        self.ai_tab_text.render_dst.dst = self.ai_tab.render_dst.dst
        self.ai_tab_text.render_dst.dst.x += 4
        self.ai_tab_text.render_dst.dst.y += 6
        renderable.set_sprite(game, self.status_tab)
        renderable.set_sprite(game, self.inventory_tab)
        renderable.set_sprite(game, self.ability_tab)
        renderable.set_sprite(game, self.job_change_tab)
        renderable.set_sprite(game, self.ai_tab)
        renderable.set_text_lg(game, self.status_tab_text)
        renderable.set_text_lg(game, self.inventory_tab_text)
        renderable.set_text_lg(game, self.ability_tab_text)
        renderable.set_text_lg(game, self.job_change_tab_text)
        renderable.set_text_lg(game, self.ai_tab_text)

        # slots
        player_guild = game.world.guilds.at(0)
        for i in range(self.unit_slots.size):
            unit_slot = self.unit_slots.at(i)
            unit_slot.render_dst.dst = slot_dst
            renderable.set_sprite(game, unit_slot)

            # get unit from guild
            if i <= player_guild.unit_handles.size - 1:
                unit_handle = player_guild.unit_handles[i]
                unit_dst = slot_dst
                unit_dst.x += slot_padding
                unit_dst.y += slot_padding
                renderable.set_unit(game, unit_handle, unit_dst)

            # inc slot dst
            slot_dst.x += slot_inc.x
            if i == wrap_at_idx:
                wrap_at_idx += cols
                slot_dst.x = start_slot_dst.x
                slot_dst.y += slot_inc.y

        if self.active_tab == UnitsWindowTabName.Status:
            self.update_status_tab(game)
        elif self.active_tab == UnitsWindowTabName.Inventory:
            self.update_inventory_tab(game)
        elif self.active_tab == UnitsWindowTabName.Ability:
            self.update_ability_tab(game)
        elif self.active_tab == UnitsWindowTabName.JobChange:
            self.update_job_change_tab(game)
        elif self.active_tab == UnitsWindowTabName.AI:
            self.update_ai_tab(game)

    def update_status_tab(self, game: Game):
        renderable = UIRenderable()
        background_dst = self.background.render_dst.dst
        player_guild = game.world.guilds.at(0)
        active_unit_handle = player_guild.unit_handles[self.active_slot_idx]
        active_unit = game.world.units.at(active_unit_handle)
        # active unit content
        active_unit_dst = create_rect(
            background_dst.x + 350, background_dst.y + 100, 0, 0)
        renderable.set_unit(game, active_unit.handle, active_unit_dst)

        # stats
        self.job_text.render_dst.dst = active_unit_dst
        self.level_text.render_dst.dst = active_unit_dst
        self.job_level_text.render_dst.dst = active_unit_dst
        self.experience_text.render_dst.dst = active_unit_dst
        self.job_experience_text.render_dst.dst = active_unit_dst
        self.strength_text.render_dst.dst = active_unit_dst
        self.intelligence_text.render_dst.dst = active_unit_dst
        self.dexterity_text.render_dst.dst = active_unit_dst
        self.vitality_text.render_dst.dst = active_unit_dst
        self.agility_text.render_dst.dst = active_unit_dst
        self.luck_text.render_dst.dst = active_unit_dst

        text_y_diff = 20
        self.job_text.render_dst.dst.y -= 20
        self.level_text.render_dst.dst.x -= 75
        self.experience_text.render_dst.dst = self.level_text.render_dst.dst
        self.experience_text.render_dst.dst.y += text_y_diff
        self.job_level_text.render_dst.dst = self.experience_text.render_dst.dst
        self.job_level_text.render_dst.dst.y += text_y_diff
        self.job_experience_text.render_dst.dst = self.job_level_text.render_dst.dst
        self.job_experience_text.render_dst.dst.y += text_y_diff
        self.strength_text.render_dst.dst.x += 50
        self.intelligence_text.render_dst.dst.x = self.strength_text.render_dst.dst.x
        self.intelligence_text.render_dst.dst.y += text_y_diff
        self.dexterity_text.render_dst.dst.x = self.strength_text.render_dst.dst.x
        self.dexterity_text.render_dst.dst.y += text_y_diff * 2
        self.vitality_text.render_dst.dst.x = self.strength_text.render_dst.dst.x
        self.vitality_text.render_dst.dst.y += text_y_diff * 3
        self.agility_text.render_dst.dst.x = self.strength_text.render_dst.dst.x
        self.agility_text.render_dst.dst.y += text_y_diff * 4
        self.luck_text.render_dst.dst.x = self.strength_text.render_dst.dst.x
        self.luck_text.render_dst.dst.y += text_y_diff * 5
        self.available_stat_points_text.render_dst.dst = self.strength_text.render_dst.dst
        self.available_stat_points_text.render_dst.dst.x += 0
        self.available_stat_points_text.render_dst.dst.y -= text_y_diff

        self.job_text.str.string_set(active_unit.display_name)
        sprintf(self.level_text.str, "Lvl. %d", active_unit.stats.level)
        sprintf(self.job_level_text.str, "Job Lvl. %d",
                active_unit.stats.job_level)
        sprintf(self.experience_text.str, "Exp: %lu / %lu",
                active_unit.stats.experience.value, active_unit.stats.experience.max)
        sprintf(self.job_experience_text.str, "Job Exp: %lu / %lu",
                active_unit.stats.job_experience.value, active_unit.stats.job_experience.max)
        sprintf(self.strength_text.str, "Strength: %lu",
                active_unit.stats.strength.value)
        sprintf(self.intelligence_text.str, "Intelligence: %lu",
                active_unit.stats.intelligence.value)
        sprintf(self.dexterity_text.str, "Dexterity: %lu",
                active_unit.stats.dexterity.value)
        sprintf(self.vitality_text.str, "Vitality: %lu",
                active_unit.stats.vitality.value)
        sprintf(self.agility_text.str, "Agility: %lu",
                active_unit.stats.agility.value)
        sprintf(self.luck_text.str, "Luck: %lu",
                active_unit.stats.luck.value)

        sprintf(self.available_stat_points_text.str,
                "Available Stat Points: %d", active_unit.available_stat_points)
        renderable.set_text_lg(game, self.available_stat_points_text)

        stat_button_dst = self.strength_text.render_dst.dst
        stat_button_dst.x += 80
        stat_button_dst.y -= 1
        for i, stat_button in enumerate(self.increase_stat_buttons):
            stat_name = cast(i + 1, "StatName")
            stat_icon = self.increase_stat_icons.at(i)
            stat_cost_text = self.increase_stat_cost_texts.at(i)
            stat_button.render_dst.dst = stat_button_dst
            stat_icon.render_dst.dst = stat_button_dst
            stat_icon.render_dst.dst.x += 2
            stat_icon.render_dst.dst.y += 3
            stat_cost_text.render_dst.dst = stat_button_dst
            stat_cost_text.render_dst.dst.x += 16
            stat_cost = 0
            if stat_name == StatName.Strength:
                stat_cost = get_stat_cost(active_unit.stats.strength.value)
                sprintf(stat_cost_text.str, "%d", stat_cost)
            elif stat_name == StatName.Intelligence:
                stat_cost = get_stat_cost(
                    active_unit.stats.intelligence.value)
                sprintf(stat_cost_text.str, "%d", stat_cost)
            elif stat_name == StatName.Dexterity:
                stat_cost = get_stat_cost(
                    active_unit.stats.dexterity.value)
                sprintf(stat_cost_text.str, "%d", stat_cost)
            elif stat_name == StatName.Vitality:
                stat_cost = get_stat_cost(active_unit.stats.vitality.value)
                sprintf(stat_cost_text.str, "%d", stat_cost)
            elif stat_name == StatName.Agility:
                stat_cost = get_stat_cost(active_unit.stats.agility.value)
                sprintf(stat_cost_text.str, "%d", stat_cost)
            elif stat_name == StatName.Luck:
                stat_cost = get_stat_cost(active_unit.stats.luck.value)
                sprintf(stat_cost_text.str, "%d", stat_cost)
            if active_unit.available_stat_points >= stat_cost:
                renderable.set_sprite(game, stat_button)
                renderable.set_sprite(game, stat_icon)
            renderable.set_text_lg(game, stat_cost_text)
            stat_button_dst.y += text_y_diff

        renderable.set_text_lg(game, self.job_text)
        renderable.set_text_lg(game, self.level_text)
        renderable.set_text_lg(game, self.experience_text)
        renderable.set_text_lg(game, self.job_level_text)
        renderable.set_text_lg(game, self.job_experience_text)
        renderable.set_text_lg(game, self.strength_text)
        renderable.set_text_lg(game, self.intelligence_text)
        renderable.set_text_lg(game, self.dexterity_text)
        renderable.set_text_lg(game, self.vitality_text)
        renderable.set_text_lg(game, self.agility_text)
        renderable.set_text_lg(game, self.luck_text)

    def update_inventory_tab(self, game: Game):
        renderable = UIRenderable()
        background_dst = self.background.render_dst.dst
        player_guild = game.world.guilds.at(0)
        active_unit_handle = player_guild.unit_handles[self.active_slot_idx]
        active_unit = game.world.units.at(active_unit_handle)
        active_unit_dst = create_rect(
            background_dst.x + 210, background_dst.y + 70, 0, 0)
        renderable.set_unit(game, active_unit.handle, active_unit_dst)
        slot_dst = background_dst
        slot_dst.x += 250
        slot_dst.y += 70
        start_slot_dst = slot_dst
        slot_inc = create_point(25, 25)
        cols = 10
        wrap_at_idx = cols - 1
        for i in range(self.inventory_slots.size):
            inventory_slot = self.inventory_slots.at(i)
            inventory_quantity_text = self.inventory_quantity_texts.at(i)
            inventory_slot.render_dst.dst = slot_dst
            inventory_quantity_text.render_dst.dst = slot_dst
            inventory_quantity_text.render_dst.dst.x += 16
            inventory_quantity_text.render_dst.dst.y += 12
            renderable.set_sprite(game, inventory_slot)

            inventory_item = active_unit.inventory.slots.at(i)
            if not(inventory_item.slot_is_empty):
                inventory_item_dst = slot_dst
                inventory_item_dst.x += 2
                inventory_item_dst.y += 2
                sprintf(inventory_quantity_text.str, "%d",
                        inventory_item.shared_item.quantity)
                renderable.set_regular_sprite(game,
                                              inventory_item.shared_item.item.sprite, inventory_item_dst)
                renderable.set_text_lg(game, inventory_quantity_text)

            # inc slot dst
            slot_dst.x += slot_inc.x
            if i == wrap_at_idx:
                wrap_at_idx += cols
                slot_dst.x = start_slot_dst.x
                slot_dst.y += slot_inc.y

    def update_ability_tab(self, game: Game):
        renderable = UIRenderable()
        background_dst = self.background.render_dst.dst
        player_guild = game.world.guilds.at(0)
        active_unit_handle = player_guild.unit_handles[self.active_slot_idx]
        active_unit = game.world.units.at(active_unit_handle)
        active_unit_dst = create_rect(
            background_dst.x + 210, background_dst.y + 70, 0, 0)
        renderable.set_unit(game, active_unit.handle, active_unit_dst)
        sprintf(self.available_skill_points_text.str,
                "Available Skill Points: %d", active_unit.available_skill_points)
        self.available_skill_points_text.render_dst.dst = active_unit_dst
        self.available_skill_points_text.render_dst.dst.x += 100
        renderable.set_text_lg(game, self.available_skill_points_text)
        slot_dst = background_dst
        slot_dst.x += 250
        slot_dst.y += 90
        start_slot_dst = slot_dst
        slot_inc = create_point(25, 25)
        cols = 10
        wrap_at_idx = cols - 1
        for i in range(self.ability_slots.size):
            ability_slot = self.ability_slots.at(i)
            ability_skill_point_text = self.ability_skill_point_texts.at(i)
            ability_slot.render_dst.dst = slot_dst
            ability_skill_point_text.render_dst.dst = slot_dst
            ability_skill_point_text.render_dst.dst.x += 16
            ability_skill_point_text.render_dst.dst.y += 12
            renderable.set_sprite(game, ability_slot)

            if i <= active_unit.job_abilities.size - 1:
                job_ability = active_unit.job_abilities.at(i)
                # is_ability_learned = active_unit.is_ability_learned(job_ability.ability.ability_name)
                ability_skill_points = active_unit.get_ability_skill_points(
                    job_ability.ability.ability_name)
                job_ability_dst = slot_dst
                job_ability_dst.x += 2
                job_ability_dst.y += 2
                sprintf(ability_skill_point_text.str,
                        "%d", ability_skill_points)
                renderable.set_regular_sprite(game,
                                              job_ability.ability.portrait, job_ability_dst)
                renderable.set_text_lg(game, ability_skill_point_text)

            # inc slot dst
            slot_dst.x += slot_inc.x
            if i == wrap_at_idx:
                wrap_at_idx += cols
                slot_dst.x = start_slot_dst.x
                slot_dst.y += slot_inc.y

    def update_job_change_tab(self, game: Game):
        renderable = UIRenderable()
        background_dst = self.background.render_dst.dst
        player_guild = game.world.guilds.at(0)
        active_unit_handle = player_guild.unit_handles[self.active_slot_idx]
        active_unit = game.world.units.at(active_unit_handle)
        active_unit_dst = create_rect(
            background_dst.x + 350, background_dst.y + 100, 0, 0)
        job_tier = get_unit_name_job_tier(active_unit.unit_name)
        can_job_change = unit_can_job_change(
            active_unit.unit_name, active_unit.stats.job_level)
        job_row_1_x = background_dst.x + 335
        job_row_2_x = background_dst.x + 235
        job_row_1_y = background_dst.y + 70
        job_row_2_y = job_row_1_y + 70
        job_row_3_y = job_row_2_y + 70
        unit = game.unit_db.get_unit(UnitName.Explorer)
        active_unit_dst = create_rect(
            job_row_1_x, job_row_1_y, 0, 0)
        renderable.set_unit_sprite(game, unit.sprite, active_unit_dst)

        slot_dst = create_rect(job_row_2_x, job_row_2_y, 0, 0)
        slot_row_3_dst = slot_dst
        slot_row_3_dst.y = job_row_3_y
        job_row_3_idx = 0
        for i, slot in enumerate(self.job_change_row_2_slots):
            slot_unit_name = slot.ui_event.unit_name
            slot.render_dst.dst = slot_dst
            had_previous_tier2_job = False
            row_3_slot_0 = self.job_change_row_3_slots.at(
                job_row_3_idx)
            job_row_3_idx += 1
            row_3_slot_1 = self.job_change_row_3_slots.at(
                job_row_3_idx)
            job_row_3_idx += 1
            if job_tier == 2:
                if row_3_slot_0.ui_event.unit_name == active_unit.unit_name or row_3_slot_1.ui_event.unit_name == active_unit.unit_name:
                    had_previous_tier2_job = True
            if can_job_change and job_tier == 0:
                renderable.set_sprite(game, slot)

            active_unit_dst = slot_dst
            active_unit_dst.x += 2
            active_unit_dst.y += 2
            can_tier_one_job_change = can_job_change and job_tier == 0
            if can_tier_one_job_change or had_previous_tier2_job:
                # render the unit sprite
                unit = game.unit_db.get_unit(slot.ui_event.unit_name)
                renderable.set_unit_sprite(game, unit.sprite, active_unit_dst)
            elif job_tier == 1 and slot.ui_event.unit_name == active_unit.unit_name:
                # render the unit sprite, if you render the unit there is one frame
                # of mismatch where the unit at handle is changed
                unit = game.unit_db.get_unit(slot.ui_event.unit_name)
                renderable.set_unit_sprite(game, unit.sprite, active_unit_dst)

            # position two offshoots from this class (job level 3 classes)
            # i.e. thief has two paths in the tree, assassin or rogue
            slot_row_3_dst = slot_dst
            slot_row_3_dst.y = job_row_3_y
            row_3_slot_0.render_dst.dst = slot_row_3_dst
            row_3_slot_1.render_dst.dst = slot_row_3_dst
            row_3_slot_0.render_dst.dst.x -= 50
            row_3_slot_1.render_dst.dst.x += 50
            row_3_slot_0_unit_dst = row_3_slot_0.render_dst.dst
            row_3_slot_0_unit_dst.x += 2
            row_3_slot_0_unit_dst.y += 2
            row_3_slot_1_unit_dst = row_3_slot_1.render_dst.dst
            row_3_slot_1_unit_dst.x += 2
            row_3_slot_1_unit_dst.y += 2
            if can_job_change and job_tier == 1 and slot_unit_name == active_unit.unit_name:
                # render slot 1
                renderable.set_sprite(game, row_3_slot_0)
                # render unit over slot
                unit = game.unit_db.get_unit(
                    row_3_slot_0.ui_event.unit_name)
                renderable.set_unit_sprite(game,
                                           unit.sprite, row_3_slot_0_unit_dst)
                # render slot 2
                renderable.set_sprite(game, row_3_slot_1)
                # render unit over slot 2
                unit = game.unit_db.get_unit(
                    row_3_slot_1.ui_event.unit_name)
                renderable.set_unit_sprite(game,
                                           unit.sprite, row_3_slot_1_unit_dst)
            elif job_tier == 2:
                if row_3_slot_0.ui_event.unit_name == active_unit.unit_name:
                    unit = game.unit_db.get_unit(
                        row_3_slot_0.ui_event.unit_name)
                    renderable.set_unit_sprite(game,
                                               unit.sprite, row_3_slot_0_unit_dst)
                elif row_3_slot_1.ui_event.unit_name == active_unit.unit_name:
                    unit = game.unit_db.get_unit(
                        row_3_slot_1.ui_event.unit_name)
                    renderable.set_unit_sprite(game,
                                               unit.sprite, row_3_slot_1_unit_dst)
            # inc slot dst
            slot_dst.x += 50

        # display when the next job change occurs
        if not(can_job_change) and job_tier != 2:
            if job_tier == 0:
                self.next_job_change_level_text.str.string_set_literal(
                    "Job Change Available at Job Lvl. 10.")
                self.next_job_change_level_text.render_dst.dst.x = background_dst.x + 270
                self.next_job_change_level_text.render_dst.dst.y = job_row_2_y
                renderable.set_text_lg(game, self.next_job_change_level_text)
            elif job_tier == 1:
                self.next_job_change_level_text.str.string_set_literal(
                    "Job Change Available at Job Lvl. 40.")
                self.next_job_change_level_text.render_dst.dst.x = background_dst.x + 270
                self.next_job_change_level_text.render_dst.dst.y = job_row_3_y
                renderable.set_text_lg(game, self.next_job_change_level_text)

    def update_ai_tab(self, game: Game):
        renderable = UIRenderable()
        background_dst = self.background.render_dst.dst
        player_guild = game.world.guilds.at(0)
        active_unit_handle = player_guild.unit_handles[self.active_slot_idx]
        active_unit = game.world.units.at(active_unit_handle)
        active_unit_dst = create_rect(
            background_dst.x + 350, background_dst.y + 100, 0, 0)
        renderable.set_unit(game, active_unit.handle, active_unit_dst)
        slot_dst = background_dst
        slot_dst.x += 250
        slot_dst.y += 90
        start_slot_dst = slot_dst
        slot_inc = create_point(50, 25)
        cols = 6
        wrap_at_idx = cols - 1
        for i, ai_ability_slot in enumerate(self.ai_ability_slots):
            ai_ability_order_text = self.ai_ability_slot_order_texts.at(i)
            ai_ability_slot.render_dst.dst = slot_dst
            ai_ability_order_text.render_dst.dst = slot_dst
            ai_ability_order_text.render_dst.dst.x += 16
            ai_ability_order_text.render_dst.dst.y += 12
            renderable.set_sprite(game, ai_ability_slot)

            if i <= active_unit.ai_abilities.size - 1:
                ai_ability = active_unit.ai_abilities.at(i)
                if not(ai_ability.is_empty):
                    ability = active_unit.abilities.at(
                        ai_ability.unit_ability_handle)
                    job_ability_dst = slot_dst
                    job_ability_dst.x += 2
                    job_ability_dst.y += 2
                    renderable.set_regular_sprite(game,
                                                  ability.ability.portrait, job_ability_dst)
            sprintf(ai_ability_order_text.str,
                    "%d", i + 1)
            renderable.set_text_lg(game, ai_ability_order_text)

            # inc slot dst
            slot_dst.y += slot_inc.y
            if i == wrap_at_idx:
                wrap_at_idx += cols
                slot_dst.x += slot_inc.x
                slot_dst.y = start_slot_dst.y
        if self.ai_ability_dropdown_visible:
            active_slot = self.ai_ability_slots.at(self.ai_ability_active_idx)
            self.ai_ability_dropdown_background.render_dst.dst = active_slot.render_dst.dst
            self.ai_ability_dropdown_background.render_dst.dst.x += 25
            self.ai_ability_dropdown_background.render_dst.dst.y += 0
            renderable.set_sprite(game, self.ai_ability_dropdown_background)

            slot_dst = self.ai_ability_dropdown_background.render_dst.dst
            slot_dst.x += 3
            slot_dst.y += 2
            start_slot_dst = slot_dst
            slot_inc = create_point(25, 25)
            cols = 3
            wrap_at_idx = cols - 1
            for i, ai_option_slot in enumerate(self.ai_ability_dropdown_options):
                ai_option_slot.render_dst.dst = slot_dst
                renderable.set_sprite(game, ai_option_slot)
                # display delete button at last slot
                if i == self.ai_ability_dropdown_options.size - 1:
                    remove_icon_dst = slot_dst
                    remove_icon_dst.x += 2
                    remove_icon_dst.y += 2
                    self.ai_ability_remove_icon.render_dst.dst = remove_icon_dst
                    renderable.set_sprite(game, self.ai_ability_remove_icon)
                elif i <= active_unit.abilities.size - 1:
                    ability = active_unit.abilities.at(i)
                    ability_dst = slot_dst
                    ability_dst.x += 2
                    ability_dst.y += 2
                    renderable.set_regular_sprite(game,
                                                  ability.ability.portrait, ability_dst)

                # inc slot dst
                slot_dst.x += slot_inc.x
                if i == wrap_at_idx:
                    wrap_at_idx += cols
                    slot_dst.x = start_slot_dst.x
                    slot_dst.y += slot_inc.y


class MerchantsWindow:
    def __init__(self):
        self.background: UISprite = None
        self.window_text: TextLG = None
        self.window_close_button: UISprite = None
        self.unit_slots: Array[UISprite] = Array[UISprite](30)
        self.active_slot_idx: int = None
        self.visible: bool = None

    def init(self, game: Game):
        # unit slots needs to have the same capacity as guild.unit_handles
        self.background.render_dst.is_camera_rendered = False
        self.background.anim_speed = 100
        self.background.ui_event.event_name = UIEventName.MerchantsWindowBackground
        background_src = create_rect(640, 1786, 544, 262)
        self.background.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, background_src)
        self.window_close_button.render_dst.is_camera_rendered = False
        self.window_close_button.anim_speed = 100
        self.window_close_button.ui_event.event_name = UIEventName.MerchantsWindowClose
        close_button_src = create_rect(10, 1664, 10, 10)
        self.window_close_button.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, close_button_src)

        text_color = create_color(255, 255, 255, 255)
        text_outline_color = create_color(0, 0, 0, 255)
        text_dst = create_point(0, 0)
        self.window_text.text_set(game, "Merchants", text_dst, FontStyle.Bold, TextAlignment.Left,
                                  TextWordWrap.NoWrap, 500, 12, text_color, 1, text_outline_color, False)

        # set units slots size
        self.unit_slots.size = array_capacity(self.unit_slots)
        for i in range(self.unit_slots.size):
            unit_slot = self.unit_slots.at(i)
            unit_slot.render_dst.is_camera_rendered = False
            unit_slot.anim_speed = 100
            unit_slot.ui_event.event_name = UIEventName.MerchantsWindowSlot
            unit_slot.ui_event.handle = i
            # always showing the player's guild for now
            unit_slot.ui_event.guild_handle = 0
            slot_src = create_rect(0, 320, 24, 44)
            unit_slot.shared_srcs = game.sprite_db.find(
                game, ImageName.UI, slot_src)

    def set_visible(self, visible: bool):
        self.visible = visible
        if not(self.visible):
            self.background.input_events.clear()

    def update(self, game: Game):
        if not(self.visible):
            return
        self.background.render_dst.dst.x = 0
        self.background.render_dst.dst.y = 0
        background_src = self.background.shared_srcs.srcs.at(0)
        base_res_w = game.engine.base_resolution.x
        base_res_h = game.engine.base_resolution.y
        self.background.render_dst.dst.x = base_res_w / 2 - background_src.w / 2
        self.background.render_dst.dst.y = base_res_h / 2 - background_src.h / 2
        background_dst = self.background.render_dst.dst
        self.window_text.render_dst.dst = background_dst
        self.window_text.render_dst.dst.x += 4
        self.window_text.render_dst.dst.y += 6
        self.window_close_button.render_dst.dst = background_dst
        self.window_close_button.render_dst.dst.x += background_src.w - 15
        self.window_close_button.render_dst.dst.y += 6
        slot_dst = background_dst
        slot_dst.x += 6
        slot_dst.y += 24 + 6
        start_slot_dst = slot_dst
        slot_inc = create_point(25, 45)
        slot_padding = 2
        cols = 6
        wrap_at_idx = cols - 1

        # background
        renderable = UIRenderable()
        renderable.set_sprite(game, self.background)
        renderable.set_text_lg(game, self.window_text)
        renderable.set_sprite(game, self.window_close_button)

        # slots
        player_guild = game.world.guilds.at(0)
        for i in range(self.unit_slots.size):
            unit_slot = self.unit_slots.at(i)
            unit_slot.render_dst.dst = slot_dst
            renderable.set_sprite(game, unit_slot)

            # get unit from guild
            if i <= player_guild.merchant_handles.size - 1:
                unit_handle = player_guild.merchant_handles[i]
                unit_dst = slot_dst
                unit_dst.x += slot_padding
                unit_dst.y += slot_padding
                renderable.set_unit(game, unit_handle, unit_dst)

            # inc slot dst
            slot_dst.x += slot_inc.x
            if i == wrap_at_idx:
                wrap_at_idx += cols
                slot_dst.x = start_slot_dst.x
                slot_dst.y += slot_inc.y


class GuildWindow:
    def __init__(self):
        self.background: UISprite = None
        self.window_text: TextLG = None
        self.window_close_button: UISprite = None
        self.inventory_tab: UISprite = None
        self.inventory_tab_text: TextLG = None
        self.inventory_slots: Array[UISprite] = Array[UISprite](50)
        self.inventory_quantity_texts: Array[TextLG] = Array[TextLG](50)
        self.active_slot_idx: int = None
        self.visible: bool = None

    def init(self, game: Game):
        # unit slots needs to have the same capacity as guild.unit_handles
        self.background.render_dst.is_camera_rendered = False
        self.background.anim_speed = 100
        self.background.ui_event.event_name = UIEventName.GuildWindowBackground
        background_src = create_rect(640, 1786, 544, 262)
        self.background.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, background_src)
        self.window_close_button.render_dst.is_camera_rendered = False
        self.window_close_button.anim_speed = 100
        self.window_close_button.ui_event.event_name = UIEventName.GuildWindowClose
        close_button_src = create_rect(10, 1664, 10, 10)
        self.window_close_button.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, close_button_src)
        self.inventory_tab.render_dst.is_camera_rendered = False
        self.inventory_tab.anim_speed = 100
        self.inventory_tab.ui_event.event_name = UIEventName.UnitsWindowInventoryTab
        tab_src = create_rect(0, 364, 64, 25)
        self.inventory_tab.shared_srcs = game.sprite_db.find(
            game, ImageName.UI, tab_src)

        text_color = create_color(255, 255, 255, 255)
        text_outline_color = create_color(0, 0, 0, 255)
        text_dst = create_point(0, 0)
        self.window_text.text_set(game, "League", text_dst, FontStyle.Bold, TextAlignment.Left,
                                  TextWordWrap.NoWrap, 500, 12, text_color, 1, text_outline_color, False)

        text_color = create_color(0, 0, 0, 255)
        text_outline_color = create_color(0, 0, 0, 255)
        self.inventory_tab_text.text_set(game, "Inventory", text_dst, FontStyle.Bold, TextAlignment.Left,
                                         TextWordWrap.NoWrap, 500, 12, text_color, 0, text_outline_color, False)

        # set inventory slots size
        self.inventory_slots.size = array_capacity(self.inventory_slots)
        self.inventory_quantity_texts.size = array_capacity(
            self.inventory_quantity_texts)
        if self.inventory_slots.size != self.inventory_quantity_texts.size:
            print(
                "ui_containers. UnitsWindow - inventory slots size != inventory quantity texts size.")
            exit(1)
        for i in range(self.inventory_slots.size):
            inventory_slot = self.inventory_slots.at(i)
            inventory_slot.render_dst.is_camera_rendered = False
            inventory_slot.anim_speed = 100
            slot_src = create_rect(0, 389, 24, 24)
            inventory_slot.shared_srcs = game.sprite_db.find(
                game, ImageName.UI, slot_src)

            text_color = create_color(0, 0, 0, 255)
            text_outline_color = create_color(255, 255, 255, 255)
            text_dst = create_point(0, 0)
            inventory_quantity_text = self.inventory_quantity_texts.at(i)
            inventory_quantity_text.text_set(game, "0", text_dst, FontStyle.Bold, TextAlignment.Left,
                                             TextWordWrap.NoWrap, 500, 12, text_color, 1, text_outline_color, False)

    def set_visible(self, visible: bool):
        self.visible = visible
        if not(self.visible):
            self.background.input_events.clear()

    def update(self, game: Game):
        if not(self.visible):
            return
        self.background.render_dst.dst.x = 0
        self.background.render_dst.dst.y = 0
        background_src = self.background.shared_srcs.srcs.at(0)
        base_res_w = game.engine.base_resolution.x
        base_res_h = game.engine.base_resolution.y
        self.background.render_dst.dst.x = base_res_w / 2 - background_src.w / 2
        self.background.render_dst.dst.y = base_res_h / 2 - background_src.h / 2
        background_dst = self.background.render_dst.dst
        self.window_text.render_dst.dst = background_dst
        self.window_text.render_dst.dst.x += 4
        self.window_text.render_dst.dst.y += 6
        self.window_close_button.render_dst.dst = background_dst
        self.window_close_button.render_dst.dst.x += background_src.w - 15
        self.window_close_button.render_dst.dst.y += 6
        slot_dst = background_dst
        slot_dst.x += 6
        slot_dst.y += 24 + 6
        start_slot_dst = slot_dst
        slot_inc = create_point(25, 45)
        slot_padding = 2
        cols = 6
        wrap_at_idx = cols - 1

        # background
        renderable = UIRenderable()
        renderable.set_sprite(game, self.background)
        renderable.set_text_lg(game, self.window_text)
        renderable.set_sprite(game, self.window_close_button)

        self.inventory_tab.render_dst.dst = self.background.render_dst.dst
        self.inventory_tab.render_dst.dst.x += 168
        self.inventory_tab.render_dst.dst.y += 28
        self.inventory_tab_text.render_dst.dst = self.inventory_tab.render_dst.dst
        self.inventory_tab_text.render_dst.dst.x += 4
        self.inventory_tab_text.render_dst.dst.y += 6

        renderable.set_sprite(game, self.inventory_tab)
        renderable.set_text_lg(game, self.inventory_tab_text)

        self.update_inventory_tab(game)

    def update_inventory_tab(self, game: Game):
        renderable = UIRenderable()
        background_dst = self.background.render_dst.dst
        player_guild = game.world.guilds.at(0)
        slot_dst = background_dst
        slot_dst.x += 250
        slot_dst.y += 70
        start_slot_dst = slot_dst
        slot_inc = create_point(25, 25)
        cols = 10
        wrap_at_idx = cols - 1
        for i in range(self.inventory_slots.size):
            inventory_slot = self.inventory_slots.at(i)
            inventory_quantity_text = self.inventory_quantity_texts.at(i)
            inventory_slot.render_dst.dst = slot_dst
            inventory_quantity_text.render_dst.dst = slot_dst
            inventory_quantity_text.render_dst.dst.x += 16
            inventory_quantity_text.render_dst.dst.y += 12
            renderable.set_sprite(game, inventory_slot)

            inventory_item = player_guild.inventory.slots.at(i)
            if not(inventory_item.slot_is_empty):
                inventory_item_dst = slot_dst
                inventory_item_dst.x += 2
                inventory_item_dst.y += 2
                sprintf(inventory_quantity_text.str, "%d",
                        inventory_item.shared_item.quantity)
                renderable.set_regular_sprite(game,
                                              inventory_item.shared_item.item.sprite, inventory_item_dst)
                renderable.set_text_lg(game, inventory_quantity_text)

            # inc slot dst
            slot_dst.x += slot_inc.x
            if i == wrap_at_idx:
                wrap_at_idx += cols
                slot_dst.x = start_slot_dst.x
                slot_dst.y += slot_inc.y
