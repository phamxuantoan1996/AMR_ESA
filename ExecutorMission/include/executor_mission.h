#ifndef EXECUTOR_MISSION_H
#define EXECUTOR_MISSION_H

#include <iostream>
#include <state_mission.h>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

#include <vector>
#include <mission_job.h>

class ExecutorMission {
    public:
        ExecutorMission();
        ~ExecutorMission();

        void start();
        void stop();

        void submit();

        void pause();
        void resume();
        void cancel();

    private:
        void workerLoop();

    private:
        std::thread worker_;
        std::mutex mutex_;
        std::condition_variable cv_;



    


};

#endif