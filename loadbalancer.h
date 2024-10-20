#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <queue>
#include "request.h"
#include "webserver.h"

class LoadBalancer {
    private:
    std::queue<Request*> requestQueue;
    std::vector<WebServer*> servers;
    int num_servers;
    int time;

    public:
    static const int SCALE_FACTOR = 2;  // defines the acceptable difference between num_reqests, num_servers before autoscaling
    LoadBalancer(int _num_servers);
    void accept_request(Request* request);
    void process_requests();
    void update_time(int _time);
    void autoscale();
    void log_status();
};

#endif