#include "webserver.h"
#include <iostream>

WebServer::WebServer() {
    endtime = 0;
}

void WebServer::processRequest(Request* request, int time) {
    endtime = request->execution_time + time;
}

bool WebServer::is_busy(int time) {
    if (time >= endtime) return false;
    else return true;
}