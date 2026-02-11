#ifndef STATE_MISSION_H
#define STATE_MISSION_H

#include <iostream>
#include "state_types.h"

class StateMission;
class IStateMission{

    public:
        virtual void create()
        {
            throw std::logic_error("creating function haven't implemented");
        }
        virtual void executeJob()
        {
            throw std::logic_error("execute job function state haven't implemented");
        }
        virtual void complete()
        {
            throw std::logic_error("complete state haven't implemented");
        }
        virtual void fail()
        {
            throw std::logic_error("fail state haven't implemented");
        }

        virtual void pause()
        {
            throw std::logic_error("pause state haven't implemented");
        }

        virtual void onEnter() = 0;
        virtual void onExit() = 0;
        virtual MissionStateType getType() const = 0;
        virtual ~IStateMission() = default; 
};

class StateMission{
    private:
        IStateMission *state_;
        MissionStateType current_state_type_;
    public:
        StateMission();
        void create();
        void executeJob();
        void complete();
        void fail();
        void pause();
        void changeState(IStateMission& newState);
};

class CreateStateMission : public IStateMission {
    public:
        static CreateStateMission& instance();
        void create() override;
        void onEnter() override {
            std::cout << "Entering Create State\n";
        }
        void onExit() override {
            std::cout << "Exiting Create State\n";
        }
        virtual MissionStateType getType() const override {
            return MissionStateType::Create;
        }
};

class ExecuteJobStateMission : public IStateMission {
    public:
        static ExecuteJobStateMission& instance();
        void executeJob() override;
        void onEnter() override {
            std::cout << "Entering Execute Job State\n";
        }
        void onExit() override {
            std::cout << "Exiting Execute Job State\n";
        }
        virtual MissionStateType getType() const override {
            return MissionStateType::ExecuteJob;
        }
};

class CompleteStateMission : public IStateMission {
    public:
        static CompleteStateMission& instance();
        void complete() override;
        void onEnter() override {
            std::cout << "Entering Complete State\n";
        }
        void onExit() override {
            std::cout << "Exiting Complete State\n";
        }
        virtual MissionStateType getType() const override {
            return MissionStateType::Complete;
        }
};

class FailStateMission : public IStateMission {
    public:
        static FailStateMission& instance();
        void fail() override;
        void onEnter() override {
            std::cout << "Entering Fail State\n";
        }
        void onExit() override {
            std::cout << "Exiting Fail State\n";
        }
        virtual MissionStateType getType() const override {
            return MissionStateType::Fail;
        }
};

class PauseStateMission : public IStateMission {
    public:
        static PauseStateMission& instance();
        void pause() override;
        void onEnter() override {
            std::cout << "Entering Pause State\n";
        }
        void onExit() override {
            std::cout << "Exiting Pause State\n";
        }
        virtual MissionStateType getType() const override {
            return MissionStateType::Pause;
        }
};

#endif