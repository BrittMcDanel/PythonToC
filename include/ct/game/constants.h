#ifndef GAME_CONSTANTS
#define GAME_CONSTANTS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"

struct CT_StackTrace;

typedef enum ItemName {
  ItemName_NA,
  ItemName_Jelly,
  ItemName_FurPelt,
  ItemName_Branch,
  ItemName_Mushroom,
  ItemName_BatWing,
  ItemName_Apple,
} ItemName;

typedef enum AbilityName {
  AbilityName_NA,
  AbilityName_MeleeAttack,
  AbilityName_Fire,
} AbilityName;

typedef enum UnitName {
  UnitName_NA,
  UnitName_RandomTownsPerson0,
  UnitName_Merchant,
  UnitName_Explorer,
  UnitName_Mage,
  UnitName_Wizard,
  UnitName_Scholar,
  UnitName_Slime,
  UnitName_Bunny,
  UnitName_Bat,
  UnitName_Stump,
  UnitName_Shroomed,
} UnitName;

typedef enum UnitType {
  UnitType_NA,
  UnitType_TownsPerson,
} UnitType;

typedef enum BuildingName {
  BuildingName_NA,
  BuildingName_PlayerLeague,
  BuildingName_Shop0,
  BuildingName_RecruitmentCenter0,
  BuildingName_TeleportationStone,
} BuildingName;

typedef enum BuildingType {
  BuildingType_NA,
  BuildingType_League,
  BuildingType_PotionShop,
  BuildingType_RecruitmentShop,
} BuildingType;

typedef enum Faction {
  Faction_NA,
  Faction_Ally,
  Faction_Guild,
  Faction_Enemy,
  Faction_Neutral,
} Faction;

typedef enum WarpPointName {
  WarpPointName_NA,
  WarpPointName_Standard,
  WarpPointName_Town,
  WarpPointName_Forest,
} WarpPointName;

typedef enum SEAudioName {
  SEAudioName_NA,
  SEAudioName_Sword,
} SEAudioName;

typedef enum TextAlignment {
  TextAlignment_Left,
  TextAlignment_Center,
  TextAlignment_Right,
} TextAlignment;

typedef enum TextWordWrap {
  TextWordWrap_NoWrap,
  TextWordWrap_Wrap,
} TextWordWrap;

typedef enum ImageName {
  ImageName_NA,
  ImageName_UI,
  ImageName_Tiles,
  ImageName_Units,
  ImageName_Abilities,
  ImageName_Buildings,
  ImageName_Misc,
  ImageName_Items,
  ImageName_Monsters,
} ImageName;

typedef enum UnitAIState {
  UnitAIState_NA,
  UnitAIState_Battle,
  UnitAIState_Selling,
  UnitAIState_MerchantRestocking,
  UnitAIState_MerchantSelling,
  UnitAIState_RandomTownMove,
  UnitAIState_MovingToBuyAtMerchant,
} UnitAIState;

typedef enum FontStyle {
  FontStyle_Normal,
  FontStyle_Bold,
  FontStyle_Italic,
} FontStyle;

typedef enum UnitAnimState {
  UnitAnimState_NA,
  UnitAnimState_Idle,
  UnitAnimState_Walk,
  UnitAnimState_Attack,
  UnitAnimState_Cast,
  UnitAnimState_Hit,
  UnitAnimState_Dead,
  UnitAnimState_Sit,
} UnitAnimState;

typedef enum HandleType {
  HandleType_NA,
  HandleType_Map,
  HandleType_Building,
  HandleType_Unit,
  HandleType_Guild,
  HandleType_Item,
  HandleType_Ability,
  HandleType_TweenXY,
  HandleType_DamageText,
} HandleType;

typedef enum AIAbilityCondition {
  AIAbilityCondition_NA,
  AIAbilityCondition_Always,
} AIAbilityCondition;

typedef enum TweenHigherLevelType {
  TweenHigherLevelType_NA,
  TweenHigherLevelType_Move,
} TweenHigherLevelType;

typedef enum BGMAudioName {
  BGMAudioName_NA,
  BGMAudioName_Forest,
} BGMAudioName;

typedef enum SpriteName {
  SpriteName_NA,
  SpriteName_Warp,
} SpriteName;

typedef enum StatName {
  StatName_NA,
  StatName_Strength,
  StatName_Intelligence,
  StatName_Dexterity,
  StatName_Vitality,
  StatName_Agility,
  StatName_Luck,
} StatName;

typedef enum ItemType {
  ItemType_NA,
  ItemType_Misc,
  ItemType_Useable,
} ItemType;

typedef enum TweenType {
  TweenType_NA,
  TweenType_UnitMove,
  TweenType_UnitMoveToGuildBuilding,
  TweenType_UnitMoveToShop,
  TweenType_UnitMoveToTeleporter,
  TweenType_UnitMoveToWarpPoint,
  TweenType_UnitMoveToSetupMerchantShop,
  TweenType_UnitRandomTownMove,
  TweenType_UnitMoveToBuyAtMerchantShop,
  TweenType_UnitBuyingAtMerchantShop,
  TweenType_UnitInShop,
  TweenType_UnitInGuildBuilding,
  TweenType_PerformAbility,
  TweenType_ItemDrop,
  TweenType_DamageText,
} TweenType;

typedef enum UIEventName {
  UIEventName_NA,
  UIEventName_BuyRecruitModal,
  UIEventName_BuyRecruitBackdrop,
  UIEventName_BuyRecruitClose,
  UIEventName_BuyExplorer,
  UIEventName_BuyMerchant,
  UIEventName_UnitsWindowBackground,
  UIEventName_UnitsWindowOpen,
  UIEventName_UnitsWindowClose,
  UIEventName_UnitsWindowSlot,
  UIEventName_UnitsWindowStatusTab,
  UIEventName_UnitsWindowInventoryTab,
  UIEventName_UnitsWindowAbilityTab,
  UIEventName_UnitsWindowJobChangeTab,
  UIEventName_UnitsWindowAITab,
  UIEventName_UnitsWindowJobChange,
  UIEventName_UnitsWindowLearnAbility,
  UIEventName_UnitsWindowIncreaseStats,
  UIEventName_UnitsWindowAISelect,
  UIEventName_UnitsWindowAISelectOption,
  UIEventName_UnitsWindowAISelectBackground,
  UIEventName_MerchantsWindowBackground,
  UIEventName_MerchantsWindowOpen,
  UIEventName_MerchantsWindowClose,
  UIEventName_MerchantsWindowSlot,
  UIEventName_GuildWindowBackground,
  UIEventName_GuildWindowOpen,
  UIEventName_GuildWindowClose,
} UIEventName;

typedef enum UnitsWindowTabName {
  UnitsWindowTabName_NA,
  UnitsWindowTabName_Status,
  UnitsWindowTabName_Inventory,
  UnitsWindowTabName_Ability,
  UnitsWindowTabName_JobChange,
  UnitsWindowTabName_AI,
} UnitsWindowTabName;


#endif // GAME_CONSTANTS
