#ifndef MISSION_JOB_H
#define MISSION_JOB_H
#include <string>
#include <variant>
#include <memory>
enum class JobStatus
{
    Init,
    Running,
    Finished,
    Failed
};

enum class DiscreteLevel {
    LEVEL0,
    LEVEL1,
    LEVEL2,
    LEVEL3,
    LEVEL4,
    LEVEL5,
    LEVEL6,
    LEVEL7,
    LEVEL8,
    LEVEL9
};

struct LiftLevelTarget {
    DiscreteLevel level;
};
struct LiftHeightTarget {
    float height;
};
using LiftTarget = std::variant<LiftLevelTarget,LiftHeightTarget>;

class IJobStep {
    public:
        virtual ~IJobStep() = default;
        virtual void onEnter() = 0;
        virtual void onExit() = 0;
        virtual JobStatus onTick() = 0;

        JobStatus tick()
        {
            if(status_ == JobStatus::Init)
            {
                onEnter();
                status_ = JobStatus::Running;
            }

            if(status_ == JobStatus::Running)
            {
                status_ = onTick();
            }

            if(status_ == JobStatus::Finished ||
            status_ == JobStatus::Failed)
            {
                onExit();
            }

            return status_;
        }
    protected:
        JobStatus status_{JobStatus::Init};
};

class JobStepMovePath : public IJobStep {
    public:
        JobStepMovePath(std::string target) : target_(target){
            test_reached = 0;
        };
        void onEnter() override;
        void onExit() override;
        JobStatus onTick() override;
    private:
        std::string target_;
        int test_reached;
};

/*Lift Job*/
class ILiftControl {
    public:
        void virtual moveTo(const LiftTarget& target) = 0;
        bool virtual isReached() = 0;
        bool virtual hasError() = 0;
        void virtual stop() = 0;
        virtual ~ILiftControl() = default;
};
class LiftControlLevel : public ILiftControl {
    public:
        void moveTo(const LiftTarget& target) override;
        bool isReached() override;
        bool hasError() override;
        void stop() override; 
};

class LiftControlHeight : public ILiftControl {
    public:
        void moveTo(const LiftTarget& target) override;
        bool isReached() override;
        bool hasError() override;
        void stop() override;
};

class JobStepLift : public IJobStep {
    public:
        JobStepLift(ILiftControl& lift,LiftTarget target):lift_(lift),target_(target){}
        void onEnter() override;
        void onExit() override;
        JobStatus onTick() override;
    private:
        ILiftControl& lift_;
        LiftTarget target_;
        bool started_{false};
};
/***********************************/


/*Fork Job*/
class JobStepFork : public IJobStep {
    public:
        void onEnter() override;
        void onExit() override;
        JobStatus onTick() override;
};
/***********************************/

#endif