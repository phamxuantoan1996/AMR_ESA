#ifndef MISSION_JOB_H
#define MISSION_JOB_H
#include <string>
enum class JobStatus
{
    Init,
    Running,
    Finished,
    Failed
};

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
    private:
        JobStatus status_{JobStatus::Init};
};

class MoveJobSRC : public IJobStep {
    public:
        MoveJobSRC(std::string target) : target_(target){
            test_reached = 0;
        };
        void onEnter() override;
        void onExit() override;
        JobStatus onTick() override;
    private:
        std::string target_;
        int test_reached;
};


#endif