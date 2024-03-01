#include "MathFormulaImpl.hpp"

grpc::Status MathFormulaImpl::GetFormula(
    grpc::ServerContext* context, const RequestMessage* request, ReplyMessage* reply)
{
    if (request->message().compare("addition") == 0) {
        reply->set_message("2+2=4");
        return grpc::Status::OK;
    }

    if (request->message().compare("multiplication") == 0) {
        reply->set_message("2x2=4");
        return grpc::Status::OK;
    }

    reply->set_message("???");
    return grpc::Status::OK;
}