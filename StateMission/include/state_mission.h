#ifndef STATE_AMR_H
#define STATE_AMR_H

#include <iostream>

class StateMission;
class IStateMission{

    public:
        virtual void create(StateMission& state_mission)
        {
            throw std::logic_error("creating function haven't implemented");
        }
        virtual void assign(StateMission& state_mission)
        {
            throw std::logic_error("assigning function haven't implemented");
        }
        virtual void executeJob(StateMission& state_mission)
        {
            throw std::logic_error("execute job function state haven't implemented");
        }
        virtual void complete(StateMission& state_mission)
        {
            throw std::logic_error("complete state haven't implemented");
        }
        virtual void error(StateMission& state_mission)
        {
            throw std::logic_error("error state haven't implemented");
        }
        virtual std::string name() const = 0;

        virtual ~IStateMission() = default; 
};

class StateMission{
    private:
        IStateMission *state_;
    public:
        StateMission();
        void create();
        void assign();
        void executeJob();
        void complete();
        void error();
        void changeState(IStateMission& newState);
        std::string nameState() const;
};

class CreateStateMission : public IStateMission {
    public:
        static CreateStateMission& instance();
        void create(StateMission& state_mission) override;
        std::string name() const override;
};

class AssignStateMission : public IStateMission {
    public:
        static AssignStateMission& instance();
        void assign(StateMission& state_mission) override;
        std::string name() const override;
};

class ExecuteJobStateMission : public IStateMission {
    public:
        static ExecuteJobStateMission& instance();
        void executeJob(StateMission& state_mission) override;
        std::string name() const override;
};

class CompleteStateMission : public IStateMission {
    public:
        static CompleteStateMission& instance();
        void complete(StateMission& state_mission) override;
        std::string name() const override;
};

class FailStateMission : public IStateMission {
    public:
        static FailStateMission& instance();
        void error(StateMission& state_mission) override;
        std::string name() const override;
};

#endif