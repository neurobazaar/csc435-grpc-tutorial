#include <iostream>
#include <memory>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "protos/math_formula.grpc.pb.h"

using math::MathFormula;
using math::RequestMessage;
using math::ReplyMessage;

class Client
{
    std::string address;
    std::string port;

    public:
        Client(std::string address, std::string port) : address(address), port(port) { }
        virtual ~Client() = default;

        virtual void run()
        {
            std::shared_ptr<grpc::Channel> channel;
            std::unique_ptr<MathFormula::Stub> stub;
            std::unique_ptr<grpc::ClientContext> context;
            grpc::Status status;
            RequestMessage requestMessage;
            ReplyMessage replyMessage;

            channel = grpc::CreateChannel(address + ":" + port, grpc::InsecureChannelCredentials());
            stub = MathFormula::NewStub(channel);

            context = std::make_unique<grpc::ClientContext>();
            requestMessage.set_message("addition");
            status = stub->GetFormula(context.get(), requestMessage, &replyMessage);
            if (status.ok()) {
                std::cout << replyMessage.message() << std::endl;
            }
            
            context = std::make_unique<grpc::ClientContext>();
            requestMessage.set_message("multiplication");
            status = stub->GetFormula(context.get(), requestMessage, &replyMessage);
            if (status.ok()) {
                std::cout << replyMessage.message() << std::endl;
            }

            context = std::make_unique<grpc::ClientContext>();
            requestMessage.set_message("quit");
            status = stub->GetFormula(context.get(), requestMessage, &replyMessage);
        }
};

int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cerr << "USE: ./client <IP address> <port>" << std::endl;
        return 1;
    }

    std::string address(argv[1]);
    std::string port(argv[2]);

    Client client(address, port);
    client.run();

    return 0;
}