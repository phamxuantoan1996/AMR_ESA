#include "mission_job.h"
#include <iostream>
void MoveJobSRC::onEnter()
{
    std::cout << "Robot started moving\n";
}
void MoveJobSRC::onExit()
{
    std::cout << "Robot moved to " << target_ << std::endl;
}
JobStatus MoveJobSRC::tick()
{
    // robot reached
    if(test_reached == 10)
    {
        return JobStatus::Finished;
    }
    test_reached++;
    // 
    return JobStatus::Running;
}