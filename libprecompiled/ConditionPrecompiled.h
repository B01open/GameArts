
#pragma once

#include "libstorage/Table.h"
#include <libblockverifier/ExecutiveContext.h>
#include <libdevcore/Common.h>

namespace dev
{
namespace precompiled
{
#if 0
contract Condition {
    function EQ(string, int);
    function EQ(string, string);

    function NE(string, int);
    function NE(string, string);

    function GT(string, int);
    function GE(string, int);

    function LT(string, int);
    function LE(string, int);

    function limit(int);
    function limit(int, int);
}
{
    "e44594b9": "EQ(string,int256)",
    "cd30a1d1": "EQ(string,string)",
    "42f8dd31": "GE(string,int256)",
    "08ad6333": "GT(string,int256)",
    "b6f23857": "LE(string,int256)",
    "c31c9b65": "LT(string,int256)",
    "39aef024": "NE(string,int256)",
    "2783acf5": "NE(string,string)",
    "2e0d738a": "limit(int256)",
    "7ec1cc65": "limit(int256,int256)"
}
#endif

class ConditionPrecompiled : public Precompiled
{
public:
    typedef std::shared_ptr<ConditionPrecompiled> Ptr;
    ConditionPrecompiled();
    virtual ~ConditionPrecompiled(){};


    std::string toString() override;

    bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> context, bytesConstRef param,
        Address const& origin = Address(), Address const& _sender = Address()) override;

    void setPrecompiledEngine(std::shared_ptr<dev::blockverifier::ExecutiveContext> engine)
    {
        m_exeEngine = engine;
    }

    void setCondition(dev::storage::Condition::Ptr condition) { m_condition = condition; }
    dev::storage::Condition::Ptr getCondition() { return m_condition; }

private:
    std::shared_ptr<dev::blockverifier::ExecutiveContext> m_exeEngine;
    // condition must been setted
    dev::storage::Condition::Ptr m_condition;
};

}  // namespace precompiled

}  // namespace dev
