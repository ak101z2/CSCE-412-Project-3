#include "request.h"
#include <iostream>
#include <random>

// This function was written with the help of ChatGPT to determine the random ip addresses
Request::Request() {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Randomly generate ip_in and ip_out (assuming a range, e.g., 0-255 for IP address components)
    std::uniform_int_distribution<> ip_dist(0, 255);
    ip_in = (ip_dist(gen) << 24) | (ip_dist(gen) << 16) | (ip_dist(gen) << 8) | ip_dist(gen);
    ip_out = (ip_dist(gen) << 24) | (ip_dist(gen) << 16) | (ip_dist(gen) << 8) | ip_dist(gen);

    // Choose a job type (0 for Processing, 1 for Streaming)
    std::uniform_int_distribution<> job_dist(0, 1);
    job_type = static_cast<JobType>(job_dist(gen));

    // Randomly generate execution time between 1 and 3
    std::uniform_int_distribution<> exec_time_dist(1, max_execution_time);
    execution_time = exec_time_dist(gen);
}
