#ifndef REQUEST_H
#define REQUEST_H

class Request {
public:
    static const int max_execution_time = 5;  // adjustable maximum job runtime 
    enum class JobType { Processing, Streaming };
    
    int execution_time;
    JobType job_type;
    int ip_in;
    int ip_out;

    Request();
};

#endif