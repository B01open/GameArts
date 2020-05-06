
#pragma once
#include "Common.h"
#include "Transaction.h"
#include <libdevcore/Guards.h>
#include <libdevcore/RLP.h>

namespace dev
{
namespace eth
{
class TxsParallelParser
{
    /*
        To support decode transaction parallel in a block
        Encode/Decode Protocol:
        [txNum] [[0], [offset1], [offset2] ...] [[txByte0], [txByte1], [txByte2] ...]
                            |----------------------------------^
    */
    using Offset_t = uint32_t;

public:
    static bytes encode(std::shared_ptr<Transactions> _txs);
    static bytes encode(std::vector<bytes> const& _txs);
    static void decode(std::shared_ptr<Transactions> _txs, bytesConstRef _bytes,
        CheckTransaction _checkSig = CheckTransaction::Everything, bool _withHash = false);

private:
    static inline bytes toBytes(Offset_t _num)
    {
        bytes ret(sizeof(Offset_t), 0);
        *(Offset_t*)(ret.data()) = _num;
        return ret;
    }

    static inline Offset_t fromBytes(bytesConstRef _bs) { return Offset_t(*(Offset_t*)_bs.data()); }
};

}  // namespace eth
}  // namespace dev
