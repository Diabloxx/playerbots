#pragma once
#include "InventoryAction.h"

namespace ai
{
    class QueryItemUsageAction : public InventoryAction
    {
    public:
        QueryItemUsageAction(PlayerbotAI* ai, string name = "query item usage") : InventoryAction(ai, name) {}

    protected:
        virtual bool ExecuteCommand(Event& event) override;
        uint32 GetCount(ItemPrototype const *item);
        string QueryItem(ItemPrototype const *item, uint32 count, uint32 total);
        string QueryItemUsage(ItemPrototype const *item);
        string QueryItemPrice(ItemPrototype const *item);
        string QueryQuestItem(uint32 itemId, const Quest *questTemplate, const QuestStatusData *questStatus);
        string QueryQuestItem(uint32 itemId);
        string QueryItemPower(uint32 itemId);

    private:
        ostringstream out;
    };
}
