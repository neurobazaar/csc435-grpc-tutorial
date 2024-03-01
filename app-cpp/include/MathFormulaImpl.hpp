#ifndef MATH_FORMULA_H
#define MATH_FORMULA_H

#include <grpc/grpc.h>
#include <grpcpp/server_context.h>

#include "protos/math_formula.grpc.pb.h"

#include "Server.hpp"

using math::MathFormula;
using math::RequestMessage;
using math::ReplyMessage;

class MathFormulaImpl final : public MathFormula::Service
{
    public:
        explicit MathFormulaImpl() { }
        grpc::Status GetFormula(grpc::ServerContext* context, const RequestMessage* request, ReplyMessage* reply);
        
};

#endif