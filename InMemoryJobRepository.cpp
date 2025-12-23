#include "JobRepository.h"
#include <mutex>

class InMemoryJobRepository : public JobRepository {
private:
    std::vector<Job> jobs;
    std::mutex lock;

public:
    void save(Job job) override {
        std::lock_guard<std::mutex> guard(lock);
        jobs.push_back(job);
    }

    std::vector<Job> fetchDueJobs(std::time_t now) override {
        std::lock_guard<std::mutex> guard(lock);
        std::vector<Job> due;

        for (auto &job : jobs) {
            if (job.getState() == JobState::CREATED &&
                job.getScheduledTime() <= now) {
                due.push_back(job);
            }
        }
        return due;
    }

    void update(Job job) override {
        std::lock_guard<std::mutex> guard(lock);
        for (auto &j : jobs) {
            if (j.getId() == job.getId()) {
                j = job;
                return;
            }
        }
    }
};
