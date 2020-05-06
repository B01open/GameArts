

#include "Common.h"
#include "BlockHeader.h"
#include "Exceptions.h"
#include <libdevcore/Base64.h>
#include <libdevcore/CommonIO.h>
#include <libdevcrypto/Hash.h>
#include <boost/throw_exception.hpp>

using namespace std;
using namespace dev;
using namespace dev::eth;

namespace dev
{
namespace eth
{
const unsigned c_protocolVersion = 63;
const unsigned c_minorProtocolVersion = 2;
const unsigned c_databaseBaseVersion = 9;
const unsigned c_databaseVersionModifier = 0;
const unsigned c_BlockFieldSize = 4;

const unsigned c_databaseVersion =
    c_databaseBaseVersion + (c_databaseVersionModifier << 8) + (23 << 9);

Address toAddress(std::string const& _s)
{
    try
    {
        auto b = fromHex(_s.substr(0, 2) == "0x" ? _s.substr(2) : _s, WhenError::Throw);
        if (b.size() == 20)
            return Address(b);
    }
    catch (BadHexCharacter&)
    {
    }
    BOOST_THROW_EXCEPTION(InvalidAddress());
}

static void badBlockInfo(BlockHeader const& _bi, string const& _err)
{
    string const c_line = string(80, ' ');
    string const c_border = string(2, ' ');
    string const c_space = c_border + string(76, ' ') + c_border;
    stringstream ss;
    ss << c_line << "\n";
    ss << c_space << "\n";
    ss << c_border + "  Import Failure     " + _err + string(max<int>(0, 53 - _err.size()), ' ') +
              "  " + c_border
       << "\n";
    ss << c_space << "\n";
    string bin = toString(_bi.number());
    ss << c_border +
              ("                     Bad Block #" + string(max<int>(0, 8 - bin.size()), '0') + bin +
                  "." + _bi.hash().abridged() + "                    ") +
              c_border
       << "\n";
    ss << c_space << "\n";
    ss << c_line;
    LOG(WARNING) << "\n" + ss.str();
}

void badBlock(bytesConstRef _block, string const& _err)
{
    BlockHeader bi;
    DEV_IGNORE_EXCEPTIONS(bi = BlockHeader(_block));
    badBlockInfo(bi, _err);
}

}  // namespace eth
}  // namespace dev
