#include "mission_job.h"
#include <iostream>
/****************Move Job****************/
void JobStepMovePath::onEnter()
{
    std::cout << "Robot started moving\n";

};
void JobStepMovePath::onExit()
{
    std::cout << "Robot moved to " << target_ << std::endl;
};
void JobStepMovePath::onCancel()
{
    std::cout << "cancel moving path\n";
}
void JobStepMovePath::onPause()
{
    std::cout << "pause moving path\n";
}
void JobStepMovePath::onResume()
{
    std::cout << "resume moving path\n";
}
JobStatus JobStepMovePath::onTick()
{
    // robot reached
    if(test_reached == 10)
    {
        return JobStatus::Finished;
    }
    test_reached++;
    // 
    return JobStatus::Running;
};


/*****************Lift Job***************/
void LiftControlLevel::moveTo(const LiftTarget& target)
{
    auto levelTarget = std::get<LiftLevelTarget>(target);
    std::cout << "Lift move to level : " << static_cast<int>(levelTarget.level) << std::endl;
}
bool LiftControlLevel::isReached()
{
    return true;
}
bool LiftControlLevel::hasError()
{
    return false;
}
void LiftControlLevel::stop()
{
    std::cout << "Lift stopped\n";
}
/*---------------------*/
void LiftControlHeight::moveTo(const LiftTarget& target)
{
    auto levelTarget = std::get<LiftHeightTarget>(target);
    std::cout << "Lift move to height : " << static_cast<int>(levelTarget.height) << std::endl;
}
bool LiftControlHeight::isReached()
{
    return true;
}
bool LiftControlHeight::hasError()
{
    return false;
}
void LiftControlHeight::stop()
{
    std::cout << "Lift stopped\n";
}
/*---------------------*/
void JobStepLift::onEnter()
{
    if(started_)
        return;
    started_ = true;
    lift_.moveTo(target_);
    std::cout << "Job Lift Start\n";
}
void JobStepLift::onExit()
{   
    if(status_ == JobStatus::Running)
        lift_.stop();
    std::cout << "Job Lift Exit\n";
}
void JobStepLift::onCancel()
{
    lift_.stop();
    std::cout << "cancel lifting\n";
}
void JobStepLift::onPause()
{
    lift_.stop();
    std::cout << "pause lifting\n";
}
void JobStepLift::onResume()
{
    lift_.moveTo(target_);
    std::cout << "resume lifting\n";
}
JobStatus JobStepLift::onTick()
{
    if(lift_.hasError())
        return JobStatus::Failed;
    if(lift_.isReached())
        return JobStatus::Finished;
    return JobStatus::Running;
}
/******************************************************/