#include <iostream>
#include "state_amr.h"
#include "event_bus.h"
#include "amr_events.h"

// StateAMR
StateAMR& StateAMR::instance()
{
    static StateAMR instance;
    return instance;
}
void StateAMR::changeState(IStateAMR& newState)
{
    if (state_ == &newState)
        return;
    AMRStateType old_ = currentStateType_;
    state_->onExit();
    state_ = &newState;
    state_->onEnter();
    currentStateType_ = state_->type();
    // Publish state change event
    EventBus::instance().publish<AMRStateChangedEvent>(
        AMRStateChangedEvent{old_, currentStateType_}
    );
}

// IdleStateAMR
IdleStateAMR& IdleStateAMR::instance()
{
    static IdleStateAMR instance;
    return instance;
}
void IdleStateAMR::onEnter()
{
    std::cout << "Enter Idle State\n";
}
void IdleStateAMR::onExit()
{
    std::cout << "Exit Idle State\n";
}

// BusyStateAMR
BusyStateAMR& BusyStateAMR::instance()
{
    static BusyStateAMR instance;
    return instance;
}
void BusyStateAMR::onEnter()
{
    std::cout << "Enter Busy State\n";
}
void BusyStateAMR::onExit()
{
    std::cout << "Exit Busy State\n";
}

// ErrorStateAMR
ErrorStateAMR& ErrorStateAMR::instance()
{
    static ErrorStateAMR instance;
    return instance;
}
void ErrorStateAMR::onEnter()
{
    std::cout << "Enter Error State\n";
}
void ErrorStateAMR::onExit()
{
    std::cout << "Exit Error State\n";
}