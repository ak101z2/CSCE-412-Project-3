#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "loadbalancer.h"
#include "webserver.h"
#include "request.h"

int main(int argc, char* argv[]) {

    std::srand(std::time(0));
    
    // Ensure the user passes in the correct number of arguments
    if (argc != 3) { std::cerr << "Usage: " << argv[0] << " <number_of_servers> <max_time_in_seconds>" << std::endl; return 1; }

    int num_servers = std::atoi(argv[1]);
    int runtime = std::atoi(argv[2]);

    LoadBalancer proccessing_lb(num_servers);
    LoadBalancer streaming_lb(num_servers);

    proccessing_lb.log_status();
    proccessing_lb.log_status();

    // Initialize and generate a full queue for each loadbalancer
    for (int i = 0; i < num_servers * 2 * 100; ++i) {
        Request* request = new Request();
        if (request->job_type == Request::JobType::Processing) {
            proccessing_lb.accept_request(request);
        } else if (request->job_type == Request::JobType::Streaming) {
            streaming_lb.accept_request(request);
        }
    }

    int traffic = num_servers * 0.1;  // adjustable flag controlling number of new requests
    for (int time = 1; time <= runtime; ++time) {
        proccessing_lb.update_time(time);
        streaming_lb.update_time(time);

        int num_new_requests = std::rand() % (traffic + 1);
        while (num_new_requests--) {
            Request* request = new Request();

            if (request->job_type == Request::JobType::Processing) {
                proccessing_lb.accept_request(request);
            } else if (request->job_type == Request::JobType::Streaming) {
                streaming_lb.accept_request(request);
            }
        }

        proccessing_lb.process_requests();
        streaming_lb.process_requests();

        proccessing_lb.log_status();
        proccessing_lb.log_status();
    }

    return 0;
}
