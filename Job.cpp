#include "Job.h"

Job::Job(std::string id, std::time_t time, std::string payload, int maxRetries)
    : jobId(id), scheduledTime(time), payload(payload),
      maxRetries(maxRetries), retryCount(0), state(JobState::CREATED) {}

std::string Job::getId() const { return jobId; }
std::time_t Job::getScheduledTime() const { return scheduledTime; }
JobState Job::getState() const { return state; }
int Job::getRetryCount() const { return retryCount; }
int Job::getMaxRetries() const { return maxRetries; }
std::string Job::getPayload() const { return payload; }

void Job::setState(JobState newState) {
    state = newState;
}

void Job::incrementRetry() {
    retryCount++;
}
