#ifndef MISSION_JOB_H
#define MISSION_JOB_H
#include <string>
enum class JobStatus
{
    Running,
    Finished,
    Failed
};

class IJobStep {
    public:
        virtual ~IJobStep() = default;
        virtual void onEnter() = 0;
        virtual void onExit() = 0;
        virtual JobStatus tick() = 0;
};

class MoveJobSRC : public IJobStep {
    public:
        MoveJobSRC(std::string target) : target_(target){
            test_reached = 0;
        };
        void onEnter() override;
        void onExit() override;
        JobStatus tick() override;
    private:
        std::string target_;
        int test_reached;
};


#endif