#include <iostream>
#include "state_mission.h"

//StateMission
StateMission::StateMission():state_(&CreateStateMission::instance()){}
void StateMission::create()
{
    state_->create(*this);
}
void StateMission::assign()
{
    state_->assign(*this);
}
void StateMission::executeJob()
{
    state_->executeJob(*this);
}
void StateMission::complete()
{
    state_->complete(*this);
}
void StateMission::error()
{
    state_->error(*this);
}
void StateMission::changeState(IStateMission& newState)
{
    state_ = &newState;
}
std::string StateMission::nameState() const
{
    return state_->name();
}


// CreateStateMission
CreateStateMission& CreateStateMission::instance()
{
    static CreateStateMission instance;
    return instance;
}
void CreateStateMission::create(StateMission& state_mission)
{
    std::cout << "Creating state.\n";
    //transition state
    state_mission.changeState(AssignStateMission::instance());
}
std::string CreateStateMission::name() const {
    return "Created";
}

// AssignStateMission
AssignStateMission& AssignStateMission::instance()
{
    static AssignStateMission instance;
    return instance;
}
void AssignStateMission::assign(StateMission& state_mission)
{
    std::cout << "Assigning state.\n";
    //transition state
    state_mission.changeState(ExecuteJobStateMission::instance());
};
std::string AssignStateMission::name() const
{
    return "Assigned";
}

// ExecuteJobStateMission
ExecuteJobStateMission& ExecuteJobStateMission::instance()
{
    static ExecuteJobStateMission instance;
    return instance;
}
void ExecuteJobStateMission::executeJob(StateMission& state_mission)
{
    std::cout << "Executing job\n";
    //success
    state_mission.changeState(CompleteStateMission::instance());
    //failure
}
std::string ExecuteJobStateMission::name() const
{
    return "Executing";
}

//CompleteStateMission
CompleteStateMission& CompleteStateMission::instance()
{
    static CompleteStateMission instance;
    return instance;
}
void CompleteStateMission::complete(StateMission& state_mission)
{
    std::cout << "Complete mission\n";
}
std::string CompleteStateMission::name() const
{
    return "Completed";
}

//FailStateMission
FailStateMission& FailStateMission::instance()
{
    static FailStateMission instance;
    return instance;
}
void FailStateMission::error(StateMission& state_mission)
{
    std::cout << "Error\n";
}
std::string FailStateMission::name() const
{
    return "Error";
}

//
int main(int argc,char* argv[])
{
    StateMission state;
    state.create();
    state.assign();
    state.executeJob();
    state.complete();

    return 0;
}