#include "loadbalancer.h"
#include <iostream>
#include <fstream>
#include <string>

LoadBalancer::LoadBalancer(int _num_servers) {
    time = 0;
    num_servers = _num_servers;
    for (int i = 0; i < num_servers; ++i) {
        servers.push_back(new WebServer());
    }
}

void LoadBalancer::update_time(int _time) {
    time = _time;
    if (time % 10 == 0) autoscale();
}

void LoadBalancer::accept_request(Request* request) {
    requestQueue.push(request);

    std::ofstream log_file("log.txt", std::ios::app);
    if (!log_file) { std::cerr << "Error opening log file!" << std::endl; return; }
    
    std::string jobType = (request->job_type == Request::JobType::Streaming) ? "streaming" : "processing";

    log_file << "[" << time << "] "
              << "Event: NEW REQUEST\n"
              << "Type: '" << jobType << "'\n"
              << "Job Duration: " << request->execution_time << "\n"
              << "------------------------------------------\n";

    log_file.close();
}

void LoadBalancer::process_requests() {
    for (size_t i = 0; i < servers.size(); ++i) {
        WebServer* server = servers.at(i);
        if (!server->is_busy(time)) {
            if (!requestQueue.empty()) {
                Request* request = requestQueue.front(); requestQueue.pop();
                server->processRequest(request, time);

                std::ofstream log_file("log.txt", std::ios::app);
                if (!log_file) { std::cerr << "Error opening log file!" << std::endl; return; }
                
                log_file << "[" << time << "] "
                        << "Event: SERVER PROCESSING REQUEST\n"
                        << "Server ID: '" << i << "'\n"
                        << "Job End Time: " << request->execution_time + time << "\n"
                        << "------------------------------------------\n";

                log_file.close();
            }
        }
    }
}

void LoadBalancer::autoscale() {
    int num_requests = requestQueue.size();
    int old_num_servers = num_servers;
    if (old_num_servers < 10) {
        while (servers.size() < 10) {
            servers.push_back(new WebServer());
        }
        num_servers = servers.size();
    } else {
        if (num_requests > SCALE_FACTOR * num_servers) {
            // Double number of servers
            for (int i = 0; i < num_servers; ++i) {
                servers.push_back(new WebServer());
            }
            num_servers = servers.size();
        } else if (num_servers > SCALE_FACTOR * num_requests) {
            for (auto it = servers.begin(); it != servers.end();) {
                if (num_servers < old_num_servers * 0.5) break;

                if (!((*it)->is_busy(time)) && num_servers > SCALE_FACTOR * num_requests) {
                    delete *it;
                    it = servers.erase(it);
                    --num_servers;
                } else {
                    ++it;
                }
            }
        }
    }

    std::ofstream log_file("log.txt", std::ios::app);
    if (!log_file) { std::cerr << "Error opening log file!" << std::endl; return; }
    
    log_file << "[" << time << "] "
            << "Event: LOADBALANCER AUTOSCALING\n"
            << "Initial number of servers '" << old_num_servers << "'\n"
            << "New number of servers '" << num_servers << "'\n"
            << "------------------------------------------\n";

    log_file.close();
}

void LoadBalancer::log_status() {
    std::ofstream log_file("log.txt", std::ios::app);
    if (!log_file) { std::cerr << "Error opening log file!" << std::endl; return; }

    int free_servers = 0;
    for (WebServer* server : servers) {
        if (!(server->is_busy(time))) free_servers += 1;
    }
    
    log_file << "[" << time << "] "
            << "Event: TELEMETRY\n"
            << "Free Servers: '" << free_servers << "'\n"
            << "Busy Servers: '" << servers.size() - free_servers << "'\n"
            << "Request Queue Size: '" << requestQueue.size() << "'\n"
            << "------------------------------------------\n";

    log_file.close();
}