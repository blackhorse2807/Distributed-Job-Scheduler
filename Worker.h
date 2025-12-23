#pragma once
#include "Job.h"
#include <iostream>

class Worker {
public:
    bool execute(Job &job) {
        std::cout << "Executing job: " << job.getId() << std::endl;

        // Simulate failure for demo
        if (job.getRetryCount() < 1) {
            std::cout << "Job failed\n";
            return false;
        }

        std::cout << "Job succeeded\n";
        return true;
    }
};
