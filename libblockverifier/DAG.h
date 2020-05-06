


#pragma once
#include "Common.h"
#include <libdevcore/Guards.h>
#include <tbb/concurrent_queue.h>
#include <condition_variable>
#include <cstdint>
#include <queue>
#include <thread>
#include <vector>

namespace dev
{
namespace blockverifier
{
using ID = uint32_t;
using IDs = std::vector<ID>;
static const ID INVALID_ID = (ID(0) - 1);

struct Vertex
{
    std::atomic<ID> inDegree;
    std::vector<ID> outEdge;
};

class DAG
{
    // Just algorithm, not thread safe
public:
    DAG(){};
    ~DAG();

    // Init DAG basic memory, should call before other function
    // _maxSize is max ID + 1
    void init(ID _maxSize);

    // Add edge between vertex
    void addEdge(ID _f, ID _t);

    // Generate DAG
    void generate();

    // Wait until topLevel is not empty, return INVALID_ID if DAG reach the end
    ID waitPop(bool _needWait = true);

    // Consume the top and add new top in top queue (thread safe)
    ID consume(ID _id);

    // Clear all data of this class (thread safe)
    void clear();

private:
    std::vector<std::shared_ptr<Vertex>> m_vtxs;
    tbb::concurrent_queue<ID> m_topLevel;

    ID m_totalVtxs = 0;
    std::atomic<ID> m_totalConsume;

private:
    void printVtx(ID _id);
    mutable std::mutex x_topLevel;
    std::condition_variable cv_topLevel;
};

}  // namespace blockverifier
}  // namespace dev