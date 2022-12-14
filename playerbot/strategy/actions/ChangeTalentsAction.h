#pragma once
#include "botpch.h"
#include "../../playerbot.h"
#include "../../Talentspec.h"
#include "GenericActions.h"

namespace ai
{
    class ChangeTalentsAction : public ChatCommandAction
    {
    public:
        ChangeTalentsAction(PlayerbotAI* ai, string name = "talents") : ChatCommandAction(ai, name) {}

    public:
        virtual bool ExecuteCommand(Event& event) override;
        virtual bool AutoSelectTalents(ostringstream* out);
    private:
        std::vector<TalentPath*> getPremadePaths(string findName);
        std::vector<TalentPath*> getPremadePaths(TalentSpec* oldSpec);
        TalentPath* getPremadePath(int id);
        void listPremadePaths(std::vector<TalentPath*> paths, ostringstream* out);
        TalentPath* PickPremadePath(std::vector<TalentPath*> paths, bool useProbability);
        TalentSpec* GetBestPremadeSpec(int spec);
    };

    class AutoSetTalentsAction : public ChangeTalentsAction 
    {
    public:
        AutoSetTalentsAction(PlayerbotAI* ai) : ChangeTalentsAction(ai, "auto talents") {}
        virtual bool ExecuteCommand(Event& event) override;
    };
}