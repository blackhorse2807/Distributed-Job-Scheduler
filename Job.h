#pragma once
#include <string>
#include <ctime>

enum class JobState {
    CREATED,
    SCHEDULED,
    RUNNING,
    COMPLETED,
    FAILED,
    DEAD
};

class Job {
private:
    std::string jobId;
    std::time_t scheduledTime;
    JobState state;
    int retryCount;
    int maxRetries;
    std::string payload;

public:
    Job(std::string id, std::time_t time, std::string payload, int maxRetries);

    std::string getId() const;
    std::time_t getScheduledTime() const;
    JobState getState() const;
    int getRetryCount() const;
    int getMaxRetries() const;
    std::string getPayload() const;

    void setState(JobState newState);
    void incrementRetry();
};
