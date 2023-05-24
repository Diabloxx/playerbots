#include "botpch.h"
#include "../../playerbot.h"
#include "LootStrategyValue.h"
#include "../values/ItemUsageValue.h"

using namespace ai;
using namespace std;

void LootStrategyValue::Set(string newValue)
{
    //Backwards compatibility
    if (newValue == "normal")
        newValue = "equip,vendor,quest,skill,use";
    if(newValue == "disenchant")
        newValue = "equip,vendor,disenchant,quest,skill,use";
    if (newValue == "gray")
        newValue = "equip,vendor,disenchant,quest,skill,use,vendor";
    if (newValue == "all")
        newValue = "equip,vendor,disenchant,quest,skill,use,vendor,trash";

    SubStrategyValue::Set(newValue);
}

bool LootStrategyValue::CanLoot(ItemQualifier& itemQualifier, PlayerbotAI* ai)
{
    AiObjectContext* context = ai->GetAiObjectContext();

    ItemUsage usage = AI_VALUE2(ItemUsage, "item usage", itemQualifier.GetQualifier());

    if (usage == ItemUsage::ITEM_USAGE_AMMO)
        return true;

    if(usage == ItemUsage::ITEM_USAGE_GUILD_TASK)
        return true;

    if (usage == ItemUsage::ITEM_USAGE_FORCE)
    {
        ForceItemUsage forceUsage = AI_VALUE2(ForceItemUsage, "force item usage", itemQualifier.GetQualifier());

        if (forceUsage == ForceItemUsage::FORCE_USAGE_NEED || forceUsage == ForceItemUsage::FORCE_USAGE_GREED)
            return true;
    }

    vector<string> strategies = StrSplit(AI_VALUE(string, "loot strategy"), ",");
    
    for (string& strategy : strategies) //equip,quest,skill,disenchant,use,vendor,trash
    {
        if (strategy == "equip" && (usage == ItemUsage::ITEM_USAGE_EQUIP || usage == ItemUsage::ITEM_USAGE_REPLACE))
            return true;
        if (strategy == "quest" && usage == ItemUsage::ITEM_USAGE_QUEST)
            return true;
        if (strategy == "skill" && usage == ItemUsage::ITEM_USAGE_SKILL)
            return true;
        if (strategy == "disenchant" && usage == ItemUsage::ITEM_USAGE_DISENCHANT)
            return true;
        if (strategy == "use" && usage == ItemUsage::ITEM_USAGE_USE)
            return true;
        if (strategy == "vendor" && (usage == ItemUsage::ITEM_USAGE_BAD_EQUIP || usage == ItemUsage::ITEM_USAGE_VENDOR || usage == ItemUsage::ITEM_USAGE_AH))
            return true;
        if (strategy == "trash" && usage == ItemUsage::ITEM_USAGE_NONE)
            return true;
    }

    return false;
}