#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"

class WebServer {
    public:
    WebServer();
    bool is_busy(int time);
    void processRequest(Request* req, int time);

    private:
    int endtime;
};

#endif