#pragma once
#include "MovementActions.h"
#include "GenericActions.h"

namespace ai
{
    class PositionAction : public ChatCommandAction
    {
    public:
        PositionAction(PlayerbotAI* ai) : ChatCommandAction(ai, "position") {}
        virtual bool ExecuteCommand(Event& event) override;
    };

    class MoveToPositionAction : public MovementAction
    {
    public:
        MoveToPositionAction(PlayerbotAI* ai, string name, string qualifier, bool idle = false) : MovementAction(ai, name), qualifier(qualifier), idle(idle) {}
        virtual bool Execute(Event& event);
        virtual bool isUseful();

    protected:
        string qualifier;
        bool idle;
    };

    class GuardAction : public MoveToPositionAction
    {
    public:
        GuardAction(PlayerbotAI* ai) : MoveToPositionAction(ai, "move to position", "guard") {}
    };

    class SetReturnPositionAction : public Action
    {
    public:
        SetReturnPositionAction(PlayerbotAI* ai) : Action(ai, "set return position") {}
        virtual bool Execute(Event& event);
        virtual bool isUseful();
    };

    class ReturnAction : public MoveToPositionAction
    {
    public:
        ReturnAction(PlayerbotAI* ai) : MoveToPositionAction(ai, "return", "return", true) {}
        virtual bool isUseful();
    };

    class ReturnToStayPositionAction : public MoveToPositionAction
    {
    public:
        ReturnToStayPositionAction(PlayerbotAI* ai) : MoveToPositionAction(ai, "move to position", "stay position") {}
        virtual bool isPossible();
    };
}
