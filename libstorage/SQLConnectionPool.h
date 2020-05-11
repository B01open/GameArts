 
/** @file SQLConnectionPool.h
 *  @author darrenyin
 *  @date 2019-04-24
 */

#pragma once

#include <zdb.h>
#include <iostream>
#include <memory>
#include <string>

#define SQLConnectionPool_LOG(LEVEL) LOG(LEVEL) << "[SQLConnectionPool] "

namespace dev
{
namespace storage
{
struct ConnectionPoolConfig
{
    std::string dbType;
    std::string dbIP;
    uint32_t dbPort;
    std::string dbUsername;
    std::string dbPasswd;
    std::string dbName;
    std::string dbCharset;
    uint32_t initConnections;
    uint32_t maxConnections;
};

#define SQLConnectionPool_LOG(LEVEL) LOG(LEVEL) << "[SQLConnectionPool] "

class SQLConnectionPool
{
public:
    typedef std::shared_ptr<SQLConnectionPool> Ptr;

    SQLConnectionPool(){};
    ~SQLConnectionPool();
    bool InitConnectionPool(const ConnectionPoolConfig& _dbConfig);
    Connection_T GetConnection();
    int ReturnConnection(const Connection_T& _connection);
    int BeginTransaction(const Connection_T& _connection);
    int Commit(const Connection_T& _connection);
    int RollBack(const Connection_T& _connection);

    int GetActiveConnections();
    int GetMaxConnections();

    int GetTotalConnections();

    void createDataBase(const ConnectionPoolConfig& _dbConfig);

private:
    ConnectionPool_T m_connectionPool;
    URL_T m_url;
};

inline void errorExitOut(std::stringstream& _exitInfo);

}  // namespace storage
}  // namespace dev
