#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <queue>
#include "request.h"
#include "webserver.h"

/**
 * @class LoadBalancer
 * @brief Manages incoming requests and distributes them to web servers for processing.
 * 
 * This class handles request management by maintaining a queue of incoming requests
 * and distributing them to a collection of web servers. It supports autoscaling
 * based on the current traffic load and logs status updates.
 */
class LoadBalancer {
private:
    std::queue<Request*> requestQueue;  ///< Queue of incoming requests
    std::vector<WebServer*> servers;    ///< Vector of available web servers
    int num_servers;                    ///< Number of active web servers
    int time;                           ///< Current time in seconds

public:
    /// Scale factor defines the ratio of requests to servers before autoscaling
    static const int SCALE_FACTOR = 2;  

    /**
     * @brief Constructor for LoadBalancer.
     * @param _num_servers Initial number of servers to start with.
     */
    LoadBalancer(int _num_servers);

    /**
     * @brief Accepts a new request and adds it to the queue.
     * @param request Pointer to the new request to be added.
     */
    void accept_request(Request* request);

    /**
     * @brief Processes requests by assigning them to available servers.
     */
    void process_requests();

    /**
     * @brief Updates the internal time of the LoadBalancer.
     * @param _time The current time in seconds.
     */
    void update_time(int _time);

    /**
     * @brief Automatically adjusts the number of servers based on traffic load.
     * 
     * This function scales up the number of servers if the traffic load (number
     * of requests) exceeds a certain threshold, and scales down when the traffic
     * decreases, provided the servers are idle.
     */
    void autoscale();

    /**
     * @brief Logs the status of the LoadBalancer to a file.
     * 
     * The status includes the current number of servers, the number of requests in the queue,
     * and other relevant information.
     */
    void log_status();
};

#endif