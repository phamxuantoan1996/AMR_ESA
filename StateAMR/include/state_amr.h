#ifndef STATE_AMR_H
#define STATE_AMR_H
#include <string>
#include "state_types.h"
// state design pattern + singleton

class StateAMR;
class IStateAMR
{
    public:
        virtual ~IStateAMR() = default;
        virtual void onEnter() = 0;
        virtual void onExit() = 0;
        virtual AMRStateType type() const = 0;
};

class IdleStateAMR : public IStateAMR
{
    public:
        static IdleStateAMR& instance();
        void onEnter(void) override;
        void onExit(void) override;
        AMRStateType type() const override { return AMRStateType::IDLE; }
};

class BusyStateAMR : public IStateAMR
{
    public:
        static BusyStateAMR& instance();
        void onEnter(void) override;
        void onExit(void) override;
        AMRStateType type() const override { return AMRStateType::BUSY; }
        
};

class ErrorStateAMR : public IStateAMR
{
    public:
        static ErrorStateAMR& instance();
        void onEnter(void) override;
        void onExit(void) override;
        AMRStateType type() const override { return AMRStateType::ERROR; }
};

class StateAMR
{
    private:
        IStateAMR *state_;
        StateAMR():state_(&IdleStateAMR::instance()),currentStateType_(AMRStateType::IDLE){};
        AMRStateType currentStateType_;
    public:
        static StateAMR& instance();
        void changeState(IStateAMR& newState);
        AMRStateType getCurrentStateType() const { return currentStateType_; }
};
#endif