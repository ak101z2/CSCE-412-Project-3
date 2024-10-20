#ifndef REQUEST_H
#define REQUEST_H

/**
 * @class Request
 * @brief Represents a request sent to the load balancer.
 * 
 * A request can either be for processing or streaming, and it has
 * specific attributes such as execution time and input/output IP addresses.
 */
class Request {
public:
    /// The maximum execution time for a request (in seconds).
    static const int max_execution_time = 5;

    /**
     * @enum JobType
     * @brief Defines the type of job the request is associated with.
     * 
     * - `Processing`: A job that requires computational resources for data processing.
     * - `Streaming`: A job that requires bandwidth for continuous data transfer (streaming).
     */
    enum class JobType { 
        Processing,  ///< Represents a processing request.
        Streaming    ///< Represents a streaming request.
    };

    int execution_time;  ///< The time required to execute the request.
    JobType job_type;    ///< The type of the job (Processing or Streaming).
    int ip_in;           ///< The input IP address associated with the request.
    int ip_out;          ///< The output IP address associated with the request.

    /**
     * @brief Default constructor for Request.
     * 
     * This constructor initializes a new request, randomly assigning job type, execution time,
     * and the input/output IP addresses.
     */
    Request();
};

#endif