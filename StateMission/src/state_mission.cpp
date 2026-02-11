#include <iostream>
#include "state_mission.h"
#include "amr_events.h"
#include "event_bus.h"


//StateMission
StateMission::StateMission():state_(&CreateStateMission::instance()),current_state_type_(MissionStateType::Create){
    state_->onEnter();
}
void StateMission::create()
{
    state_->create();
}
void StateMission::executeJob()
{
    state_->executeJob();
}
void StateMission::complete()
{
    state_->complete();
}
void StateMission::fail()
{
    state_->fail();
}
void StateMission::pause()
{
    state_->pause();
}
void StateMission::changeState(IStateMission& newState)
{
    if (state_ == &newState)
    {
        return;
    }
    MissionStateType old_ = current_state_type_;
    state_->onExit();
    state_ = &newState;
    newState.onEnter();
    current_state_type_ = state_->getType();
    EventBus::instance().publish(MissionStateChangedEvent{old_, current_state_type_});
}

// CreateStateMission
CreateStateMission& CreateStateMission::instance()
{
    static CreateStateMission instance;
    return instance;
}
void CreateStateMission::create()
{
    std::cout << "Creating state.\n";
}

// ExecuteJobStateMission
ExecuteJobStateMission& ExecuteJobStateMission::instance()
{
    static ExecuteJobStateMission instance;
    return instance;
}
void ExecuteJobStateMission::executeJob()
{
    std::cout << "Executing job\n";
}

//CompleteStateMission
CompleteStateMission& CompleteStateMission::instance()
{
    static CompleteStateMission instance;
    return instance;
}
void CompleteStateMission::complete()
{
    std::cout << "Complete mission\n";
}

//FailStateMission
FailStateMission& FailStateMission::instance()
{
    static FailStateMission instance;
    return instance;
}
void FailStateMission::fail()
{
    std::cout << "Failed mission\n";
}

//PauseStateMission
PauseStateMission& PauseStateMission::instance()
{
    static PauseStateMission instance;
    return instance;
}
void PauseStateMission::pause()
{
    std::cout << "Paused mission\n";
}