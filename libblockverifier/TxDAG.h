

#pragma once
#include "DAG.h"
#include "ExecutiveContext.h"
#include <libconfig/GlobalConfigure.h>
#include <libethcore/Block.h>
#include <libethcore/Transaction.h>
#include <libexecutive/Executive.h>
#include <map>
#include <memory>
#include <queue>
#include <vector>

namespace dev
{
namespace blockverifier
{
using ExecuteTxFunc =
    std::function<bool(dev::eth::Transaction::Ptr, ID, dev::executive::Executive::Ptr)>;

class TxDAGFace
{
public:
    virtual bool hasFinished() = 0;
    virtual ~TxDAGFace() {}

    // Called by thread
    // Execute a unit in DAG
    // This function can be parallel
    virtual int executeUnit(dev::executive::Executive::Ptr) = 0;

    virtual void getHaventRun(){};
};

class TxDAG : public TxDAGFace
{
public:
    TxDAG() : m_dag() {}
    virtual ~TxDAG() {}

    // Generate DAG according with given transactions
    void init(ExecutiveContext::Ptr _ctx, std::shared_ptr<dev::eth::Transactions> _txs,
        int64_t _blockHeight);

    // Set transaction execution function
    void setTxExecuteFunc(ExecuteTxFunc const& _f);

    // Called by thread
    // Has the DAG reach the end?
    // process-exit related:
    // if the g_BCOSConfig.shouldExit is true(may be the storage has exceptioned), return true
    // directly
    bool hasFinished() override
    {
        return (m_exeCnt >= m_totalParaTxs) || (g_BCOSConfig.shouldExit.load());
    }

    // Called by thread
    // Execute a unit in DAG
    // This function can be parallel
    int executeUnit(dev::executive::Executive::Ptr _executive) override;

    ID paraTxsNumber() { return m_totalParaTxs; }

    ID haveExecuteNumber() { return m_exeCnt; }

private:
    ExecuteTxFunc f_executeTx;
    std::shared_ptr<dev::eth::Transactions const> m_txs;

    DAG m_dag;

    ID m_exeCnt = 0;
    ID m_totalParaTxs = 0;

    mutable std::mutex x_exeCnt;
};

template <typename T>
class CriticalField
{
public:
    ID get(T const& _c)
    {
        auto it = m_criticals.find(_c);
        if (it == m_criticals.end())
        {
            if (m_criticalAll != INVALID_ID)
                return m_criticalAll;
            return INVALID_ID;
        }
        return it->second;
    }

    void update(T const& _c, ID _txId) { m_criticals[_c] = _txId; }

    void foreachField(std::function<bool(std::pair<T, ID>)> const& _f)
    {
        for (auto _fieldAndId : m_criticals)
        {
            if (!_f(_fieldAndId))
                break;
        }

        if (m_criticalAll != INVALID_ID)
            _f(std::pair<T, ID>(T(), m_criticalAll));
    }

    void setCriticalAll(ID _id)
    {
        m_criticalAll = _id;
        m_criticals.clear();
    }

private:
    std::map<T, ID> m_criticals;
    ID m_criticalAll = INVALID_ID;
};

}  // namespace blockverifier
}  // namespace dev
