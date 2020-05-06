
#pragma once
#include "Common.h"
#include "snappy.h"

namespace dev
{
namespace compress
{
class SnappyCompress
{
public:
    static size_t compress(bytesConstRef inputData, bytes& compressedData);
    static size_t uncompress(bytesConstRef compressedData, bytes& uncompressedData);
};
}  // namespace compress
}  // namespace dev
