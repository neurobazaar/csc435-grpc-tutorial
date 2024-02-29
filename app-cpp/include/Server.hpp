#ifndef SERVER_H
#define SERVER_H

#include <string>

#include <mutex>

class Server final : public MathFormula::Service
{
    std::string address;
    std::string port;
    int numWorkers;
    int numTerminatedWorkers;
    
    std::mutex mutex;
    
    public:
        Server(std::string address, std::string port, int numWorkers) : 
            address(address), port(port), numWorkers(numWorkers), numTerminatedWorkers(0) { }
        virtual ~Server() = default;

        virtual void run();

        virtual void workerTerminated();
};

#endif