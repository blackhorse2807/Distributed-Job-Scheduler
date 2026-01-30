#pragma once

#include "JobRepository.h"
#include "Worker.h"
#include "RetryPolicy.h"

#include <ctime>
#include <vector>

class Scheduler {
private:
    JobRepository* repository;
    Worker worker;
    RetryPolicy* retryPolicy;

public:
    Scheduler(JobRepository* repo, RetryPolicy* policy)
        : repository(repo), retryPolicy(policy) {}

    void runOnce() {
        std::time_t now = std::time(nullptr);

        // Fetch all jobs whose scheduled time has arrived
        std::vector<Job> dueJobs = repository->fetchDueJobs(now);

        for (Job& job : dueJobs) {

            // Mark job as RUNNING (soft lock)
            job.setState(JobState::RUNNING);
            repository->update(job);

            // Execute job
            bool success = worker.execute(job);

            if (success) {
                // Job completed successfully
                job.setState(JobState::COMPLETED);
            } else {
                // Job failed
                job.incrementRetry();

                if (job.getRetryCount() > job.getMaxRetries()) {
                    // Retries exhausted
                    job.setState(JobState::DEAD);
                } else {
                    // Reschedule job for retry
                    int delay = retryPolicy->getDelaySeconds(job.getRetryCount());
                    std::time_t nextRunTime = now + delay;

                    job.setScheduledTime(nextRunTime);
                    job.setState(JobState::CREATED);
                }
            }

            // Persist updated job
            repository->update(job);
        }
    }
};
