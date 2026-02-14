#ifndef EXECUTOR_MISSION_H
#define EXECUTOR_MISSION_H

#include <iostream>
#include <state_mission.h>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

#include <vector>
#include <atomic>
#include <mission_job.h>

class ExecutorMission {
    public:
        ExecutorMission(){};
        ~ExecutorMission(){};

        void start();
        void stop();

        void submit(std::vector<std::unique_ptr<IJobStep>> jobs);

        void pause();
        void resume();
        void cancel();

    private:
        void workerLoop();

    private:
        std::thread worker_;
        std::mutex mutex_;
        std::condition_variable cv_;

        std::vector<std::unique_ptr<IJobStep>> job_list_;
        bool has_job{false};
        bool system_running_{false};
        int current_index_{0};
        std::atomic<bool> pause_{false};
        std::atomic<bool> cancel_{false};
        std::atomic<bool> resume_{false};
    
};

#endif