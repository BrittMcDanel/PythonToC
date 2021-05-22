from enum import Enum


class ImageName(Enum):
    NA = 0
    UI = 0
    Tiles = 0
    Units = 0
    Abilities = 0
    Buildings = 0
    Misc = 0
    Items = 0
    Monsters = 0


class FontStyle(Enum):
    Normal = 0
    Bold = 0
    Italic = 0


class TextAlignment(Enum):
    Left = 0
    Center = 0
    Right = 0


class TextWordWrap(Enum):
    NoWrap = 0
    Wrap = 0


class Faction(Enum):
    NA = 0
    Ally = 0
    Guild = 0
    Enemy = 0
    Neutral = 0


class UnitAIState(Enum):
    NA = 0
    Battle = 0
    Selling = 0
    MerchantRestocking = 0
    MerchantSelling = 0
    RandomTownMove = 0
    MovingToBuyAtMerchant = 0


class UnitAnimState(Enum):
    NA = 0
    Idle = 0
    Walk = 0
    Attack = 0
    Cast = 0
    Hit = 0
    Dead = 0
    Sit = 0


class HandleType(Enum):
    NA = 0
    Map = 0
    Building = 0
    Unit = 0
    Guild = 0
    Item = 0
    Ability = 0
    TweenXY = 0
    DamageText = 0


class TweenHigherLevelType(Enum):
    NA = 0
    Move = 0


class TweenType(Enum):
    NA = 0
    UnitMove = 0
    UnitMoveToGuildBuilding = 0
    UnitMoveToShop = 0
    UnitMoveToTeleporter = 0
    UnitMoveToWarpPoint = 0
    UnitMoveToSetupMerchantShop = 0
    UnitRandomTownMove = 0
    UnitMoveToBuyAtMerchantShop = 0
    UnitBuyingAtMerchantShop = 0
    UnitInShop = 0
    UnitInGuildBuilding = 0
    PerformAbility = 0
    ItemDrop = 0
    DamageText = 0


class BGMAudioName(Enum):
    NA = 0
    Forest = 0


class SEAudioName(Enum):
    NA = 0
    Sword = 0


class UIEventName(Enum):
    NA = 0
    BuyRecruitModal = 0
    BuyRecruitBackdrop = 0
    BuyRecruitClose = 0
    BuyExplorer = 0
    BuyMerchant = 0
    UnitsWindowBackground = 0
    UnitsWindowOpen = 0
    UnitsWindowClose = 0
    UnitsWindowSlot = 0
    UnitsWindowStatusTab = 0
    UnitsWindowInventoryTab = 0
    UnitsWindowAbilityTab = 0
    UnitsWindowJobChangeTab = 0
    UnitsWindowAITab = 0
    UnitsWindowJobChange = 0
    UnitsWindowLearnAbility = 0
    UnitsWindowIncreaseStats = 0
    UnitsWindowAISelect = 0
    UnitsWindowAISelectOption = 0
    UnitsWindowAISelectBackground = 0
    MerchantsWindowBackground = 0
    MerchantsWindowOpen = 0
    MerchantsWindowClose = 0
    MerchantsWindowSlot = 0
    GuildWindowBackground = 0
    GuildWindowOpen = 0
    GuildWindowClose = 0


class UnitsWindowTabName(Enum):
    NA = 0
    Status = 0
    Inventory = 0
    Ability = 0
    JobChange = 0
    AI = 0


class SpriteName(Enum):
    NA = 0
    Warp = 1


class StatName(Enum):
    NA = 0
    Strength = 0
    Intelligence = 0
    Dexterity = 0
    Vitality = 0
    Agility = 0
    Luck = 0


class AIAbilityCondition(Enum):
    NA = 0
    Always = 0


class BuildingType(Enum):
    NA = 0
    League = 0
    PotionShop = 0
    RecruitmentShop = 0


class BuildingName(Enum):
    NA = 0
    PlayerLeague = 0
    Shop0 = 0
    RecruitmentCenter0 = 0
    TeleportationStone = 0


class WarpPointName(Enum):
    NA = 0
    Standard = 0
    Town = 0
    Forest = 0


class UnitType(Enum):
    NA = 0
    TownsPerson = 0


class UnitName(Enum):
    NA = 0
    RandomTownsPerson0 = 0
    Merchant = 0
    Explorer = 0
    Mage = 0
    Wizard = 0
    Scholar = 0
    Slime = 0
    Bunny = 0
    Bat = 0
    Stump = 0
    Shroomed = 0


class AbilityName(Enum):
    NA = 0
    MeleeAttack = 0
    Fire = 0


class ItemType(Enum):
    NA = 0
    Misc = 0
    Useable = 0


class ItemName(Enum):
    NA = 0
    Jelly = 0
    FurPelt = 0
    Branch = 0
    Mushroom = 0
    BatWing = 0
    Apple = 0


class SDLK(Enum):
    a = 0
    b = 0
    c = 0
    d = 0
    e = 0
    f = 0
    g = 0
    h = 0
    i = 0
    j = 0
    k = 0
    l = 0
    m = 0
    n = 0
    o = 0
    p = 0
    q = 0
    r = 0
    s = 0
    t = 0
    u = 0
    v = 0
    w = 0
    x = 0
    y = 0
    z = 0
