#ifndef AMR_STATE_MACHINE_H
#define AMR_STATE_MACHINE_H
#include <iostream>
#include <unordered_map>
#include <functional>
#include "event_bus.h"
#include "mission_events.h"
#include "amr_events.h"
#include "state_types.h"
#include <state_amr.h>

class AMRStateMachine {
    private:
        AMRStateType current_state_;
        StateAMR& state_amr_;
        std::unordered_map<AMRStateType, std::unordered_map<AMRStateType, bool>> transition_table_;
        std::unordered_map<AMRStateType, IStateAMR*> state_factory_;

        void requestTransition(AMRStateType new_state);
        void handleMissionStateChanged(const MissionStateChangedEvent& e);
    public:
        AMRStateMachine(StateAMR& state_amr);
        AMRStateType currentState() const { return current_state_; }
    
};


#endif // AMR_STATE_MACHINE_H