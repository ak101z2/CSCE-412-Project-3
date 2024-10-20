#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"

/**
 * @class WebServer
 * @brief Represents a web server that processes incoming requests.
 * 
 * The WebServer class manages the processing of requests by tracking whether it is
 * busy and how long it will take to complete the current request.
 */
class WebServer {
public:
    /**
     * @brief Default constructor for WebServer.
     * 
     * Initializes a new WebServer instance that is initially idle.
     */
    WebServer();

    /**
     * @brief Checks if the web server is busy.
     * 
     * This method checks whether the server is currently processing a request.
     * 
     * @param time The current time in seconds.
     * @return `true` if the server is busy, `false` otherwise.
     */
    bool is_busy(int time);

    /**
     * @brief Processes a given request.
     * 
     * Assigns the specified request to the server and sets the expected
     * end time for the request's processing.
     * 
     * @param req Pointer to the request to be processed.
     * @param time The current time when the request starts processing.
     */
    void processRequest(Request* req, int time);

private:
    int endtime;  ///< The time at which the server will finish processing the current request.
};

#endif