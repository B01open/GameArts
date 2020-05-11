/**
 
 *
 * @file Rpc.cpp
 * @author: caryliao
 * @date 2018-11-6
 */

#pragma once

#include <map>
#include <string>
#define INVALIDNUMBER -1
#define RPC_LOG(LEVEL) LOG(LEVEL) << "[RPC]"

namespace dev
{
namespace rpc
{
///< RPCExceptionCode
enum RPCExceptionType : int
{
    Success = 0,
    IncompleteInitialization = -40010,
    InvalidRequest = -40009,
    InvalidSystemConfig = -40008,
    NoView = -40007,
    CallFrom = -40006,
    TransactionIndex = -40005,
    BlockNumberT = -40004,
    BlockHash = -40003,
    JsonParse = -40002,
    GroupID = -40001
};

extern std::map<int, std::string> RPCMsg;


}  // namespace rpc
}  // namespace dev
