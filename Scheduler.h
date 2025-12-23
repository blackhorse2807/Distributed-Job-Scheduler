#pragma once
#include "JobRepository.h"
#include "Worker.h"
#include "RetryPolicy.h"
#include <thread>
#include <chrono>

class Scheduler {
private:
    JobRepository* repository;
    Worker worker;
    RetryPolicy* retryPolicy;

public:
    Scheduler(JobRepository* repo, RetryPolicy* retryPolicy)
        : repository(repo), retryPolicy(retryPolicy) {}

    void runOnce() {
        auto now = std::time(nullptr);
        auto jobs = repository->fetchDueJobs(now);

        for (auto &job : jobs) {
            job.setState(JobState::RUNNING);
            repository->update(job);

            bool success = worker.execute(job);

            if (success) {
                job.setState(JobState::COMPLETED);
            } else {
                job.incrementRetry();
                if (job.getRetryCount() > job.getMaxRetries()) {
                    job.setState(JobState::DEAD);
                } else {
                    job.setState(JobState::CREATED);
                    std::this_thread::sleep_for(
                        std::chrono::seconds(
                            retryPolicy->getDelaySeconds(job.getRetryCount())
                        )
                    );
                }
            }
            repository->update(job);
        }
    }
};
