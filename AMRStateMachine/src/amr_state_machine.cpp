/*
                WMS / Server
                     │
                     ▼
               AMRController   ← Facade
                 │       │
                 │       │
                 ▼       ▼
         ExecutorMission   AMRStateMachine
                 │
                 ▼
             StateMission
                 │
                 ▼
               EventBus
                 │
                 ▼
            AMRStateMachine
                 │
                 ▼
               StateAMR


*/
#include <amr_state_machine.h>

AMRStateMachine::AMRStateMachine(StateAMR& state_amr) : state_amr_(state_amr), current_state_(AMRStateType::IDLE)
{
    // Initialize transition table
    transition_table_ = {

        {AMRStateType::IDLE, {
            {AMRStateType::BUSY, true},
            {AMRStateType::ERROR, true}
        }},

        {AMRStateType::BUSY, {
            {AMRStateType::IDLE, true},
            {AMRStateType::ERROR, true}
        }},
        
        {AMRStateType::ERROR, {
            {AMRStateType::IDLE, true}
        }}
    };

    state_factory_ = {
        {AMRStateType::IDLE,  &IdleStateAMR::instance()},
        {AMRStateType::BUSY,  &BusyStateAMR::instance()},
        {AMRStateType::ERROR, &ErrorStateAMR::instance()}
    };


    // Subscribe to mission state changes

    EventBus::instance().subscribe<MissionStateChangedEvent>([this](const MissionStateChangedEvent& e)
    {
        handleMissionStateChanged(e);
    });
}

void AMRStateMachine::handleMissionStateChanged(const MissionStateChangedEvent& e)
{
    switch(e.to)
    {
        case MissionStateType::ExecuteJob:
        {
            requestTransition(AMRStateType::BUSY);
            // std::cout << "request transition Execute \n";
            break;
        }
        case MissionStateType::Complete:
        {
            requestTransition(AMRStateType::IDLE);
            // std::cout << "request transition Complete \n";
            break;
        }
        case MissionStateType::Fail:
        {
            requestTransition(AMRStateType::ERROR);
            // std::cout << "request transition Fail \n";
            break;
        }
        default:
            break;
    }
}

void AMRStateMachine::requestTransition(AMRStateType new_state)
{
    if(new_state == current_state_)
    {
        return;
    }

    // check table
    auto from_it = transition_table_.find(current_state_);
    if (from_it == transition_table_.end() ||
        from_it->second.find(new_state) == from_it->second.end())
    {
        // invalid transition
        EventBus::instance().publish(
            InvalidTransitionEvent{current_state_, new_state});
        return;
    }

    // valid transition
    AMRStateType old = current_state_;
    current_state_ = new_state;
    
    // switch(current_state_)
    // {
    //     case AMRStateType::IDLE:
    //     {
    //         state_amr_.changeState(IdleStateAMR::instance());
    //         break;
    //     }
    //     case AMRStateType::BUSY:
    //     {
    //         state_amr_.changeState(BusyStateAMR::instance());
    //         break;
    //     }
    //     case AMRStateType::ERROR:
    //     {
    //         state_amr_.changeState(ErrorStateAMR::instance());
    //         break;
    //     }
    //     default:
    //         break;
    // }
    state_amr_.changeState(*state_factory_.at(new_state));

    EventBus::instance().publish(
        AMRStateChangedEvent{old, new_state});

}