#include "MathFormulaImpl.hpp"

grpc::Status MathFormulaImpl::GetFormula(
    grpc::ServerContext* context, const RequestMessage* request, ReplyMessage* reply)
{
    server->IncReq();
    return grpc::Status::OK;
}