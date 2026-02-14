#include "executor_mission.h"
#include "event_bus.h"
#include "mission_events.h"

void ExecutorMission::submit(std::vector<std::unique_ptr<IJobStep>> jobs)
{
    // lock mutex
    std::lock_guard<std::mutex> lock(mutex_);
    job_list_ = std::move(jobs);
    current_index_ = 0;
    has_job = true;
    cv_.notify_one();
}

void ExecutorMission::workerLoop()
{
    while (system_running_)
    {
        /* code */
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock,[this]{return has_job || !system_running_;});
        if(!system_running_)
            break;
        lock.unlock();

        while(current_index_ < job_list_.size())
        {
            auto& job = job_list_[current_index_];
            if(cancel_)
            {
                //cancel job
                std::cout << "Cancel mission\n";
                job->onCancel();
                cancel_ = false;
                break;
            }

            if(pause_)
            {
                //pause job
                std::cout << "Pause mission\n";
                job->onPause();
                pause_ = false;
            }

            if(resume_)
            {
                //resume job
                std::cout << "Resume mission\n";
                job->onResume();
                resume_ = false;
            }

            auto status = job->tick();
            if(status == JobStatus::Finished)
            {
                current_index_++;
            }
            else if(status == JobStatus::Failed)
            {
                // EventBus::instance().publish(MissionFailEvent{});
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        lock.lock();
        job_list_.clear();
        current_index_ = 0;
        has_job = false;
        lock.unlock();
    }
    
}

void ExecutorMission::cancel()
{
    cancel_ = true;
}

void ExecutorMission::pause()
{
    pause_ = true;
}

void ExecutorMission::resume()
{
    resume_ = true;
}

void ExecutorMission::start()
{
    std::lock_guard<std::mutex> lock(mutex_);

    if(system_running_)
        return;  // tránh start 2 lần

    system_running_ = true;

    worker_ = std::thread(&ExecutorMission::workerLoop, this);
}

void ExecutorMission::stop()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        system_running_ = false;
        has_job = true;          // để wake khỏi wait
    }

    cv_.notify_one();

    if(worker_.joinable())
        worker_.join();
}
