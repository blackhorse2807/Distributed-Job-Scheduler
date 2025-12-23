
#include "Scheduler.h"
#include "InMemoryJobRepository.cpp"
#include "RetryPolicy.h"
#include <iostream>

int main() {
    InMemoryJobRepository repo;
    FixedRetryPolicy retryPolicy;
    Scheduler scheduler(&repo, &retryPolicy);

    std::time_t now = std::time(nullptr);

    Job job1("job-1", now, "Send Email", 3);
    repo.save(job1);

    std::cout << "Starting Scheduler...\n";

    for (int i = 0; i < 3; i++) {
        scheduler.runOnce();
    }

    return 0;
}
