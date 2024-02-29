#include "Server.hpp"

#include <iostream>
#include <vector>
#include <thread>
#include <memory>

#include "Worker.hpp"

void Server::run()
{
    std::vector<std::shared_ptr<Worker>> workers;
    std::vector<std::thread> threads;

}

void Server::workerTerminated()
{
    
}

int main(int argc, char** argv)
{
    if (argc != 4) {
        std::cerr << "USE: ./server <IP address> <port> <number of worker threads>" << std::endl;
        return 1;
    }

    std::string address(argv[1]);
    std::string port(argv[2]);
    int numWorkers(std::atoi(argv[3]));

    Server server(address, port, numWorkers);
    server.run();
    
    return 0;
}