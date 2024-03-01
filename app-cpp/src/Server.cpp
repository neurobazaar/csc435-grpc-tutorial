#include <memory>
#include <chrono>

#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpc/support/time.h>

#include "Server.hpp"
#include "MathFormulaImpl.hpp"

void Server::run()
{
    MathFormulaImpl service(this);
    
    grpc::ServerBuilder builder;
    builder.AddListeningPort(address + ":" + port, grpc::InsecureServerCredentials());
    builder.RegisterService((grpc::Service*) &service);
    RPCserver = builder.BuildAndStart();
    RPCserver->Wait();
}

void Server::IncReq()
{
    std::lock_guard<std::mutex> lock(mutex);
    numRequests++;
    if (numRequests >= 4) {
        RPCserver->Shutdown(gpr_time_from_seconds(2, GPR_CLOCK_MONOTONIC));
    }
}

int main(int argc, char** argv)
{
    if (argc != 4) {
        std::cerr << "USE: ./server <IP address> <port>" << std::endl;
        return 1;
    }

    std::string address(argv[1]);
    std::string port(argv[2]);

    Server server(address, port);
    server.run();
    
    return 0;
}