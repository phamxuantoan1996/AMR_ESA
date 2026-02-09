#include <iostream>
#include "state_amr.h"

// StateAMR
StateAMR& StateAMR::instance()
{
    static StateAMR instance;
    return instance;
}
void StateAMR::changeState(IStateAMR& newState)
{
    state_->onExit();
    state_ = &newState;
    state_->onEnter();
}
std::string StateAMR::nameState() const
{
    return state_->name();
}

// IdleStateAMR
IdleStateAMR& IdleStateAMR::instance()
{
    static IdleStateAMR instance;
    return instance;
}
std::string IdleStateAMR::name() const
{
    return "Idle";
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
std::string BusyStateAMR::name() const
{
    return "Busy";
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
std::string ErrorStateAMR::name() const
{
    return "Error";
}
void ErrorStateAMR::onEnter()
{
    std::cout << "Enter Error State\n";
}
void ErrorStateAMR::onExit()
{
    std::cout << "Exit Error State\n";
}