#include "loadbalancer.h"
#include <iostream>

LoadBalancer::LoadBalancer(int _num_servers) {
    time = 0;
    num_servers = _num_servers;
    for (int i = 0; i < num_servers; ++i) {
        servers.push_back(new WebServer());
    }
}

void LoadBalancer::update_time(int _time) {
    time = _time;
    if (time % 100 == 0) autoscale();
}

void LoadBalancer::accept_request(Request* request) {
    requestQueue.push(request);
}

void LoadBalancer::process_requests() {
    for (WebServer* server : servers) {
        if (!server->is_busy(time)) {
            if (!requestQueue.empty()) {
                Request* request = requestQueue.front(); requestQueue.pop();
                server->processRequest(request, time);
            }
        }
    }
}

void LoadBalancer::autoscale() {
    int num_requests = requestQueue.size();
    if (num_requests > SCALE_FACTOR * num_servers) {
        // Double number of servers
        for (int i = 0; i < num_servers; ++i) {
            servers.push_back(new WebServer());
        }
    } else if (num_servers > SCALE_FACTOR * num_requests) {
        // Implement later
    }
}