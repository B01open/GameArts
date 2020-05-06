
#include "SnappyCompress.h"

namespace dev
{
namespace compress
{
size_t SnappyCompress::compress(bytesConstRef inputData, bytes& compressedData)
{
    size_t compressLen;
    // auto start_t = utcTimeUs();
    compressedData.resize(snappy::MaxCompressedLength(inputData.size()));
    snappy::RawCompress(
        (const char*)inputData.data(), inputData.size(), (char*)&compressedData[0], &compressLen);
    compressedData.resize(compressLen);
    /// compress failed
    if (compressLen < 1)
    {
        LOG(ERROR) << LOG_BADGE("SnappyCompressio") << LOG_DESC("compress failed");
        return 0;
    }
#if 0
    LOG(DEBUG) << LOG_BADGE("SnappyCompress") << LOG_DESC("Compress")
               << LOG_KV("org_len", inputData.size()) << LOG_KV("compressed_len", compressLen)
               << LOG_KV("ratio", (float)inputData.size() / (float)compressedData.size())
               << LOG_KV("timecost", (utcTimeUs() - start_t));
#endif

    return compressLen;
}

size_t SnappyCompress::uncompress(bytesConstRef compressedData, bytes& uncompressedData)
{
    size_t uncompressedLen = 0;
    // auto start_t = utcTimeUs();
    snappy::GetUncompressedLength(
        (const char*)compressedData.data(), compressedData.size(), &uncompressedLen);
    uncompressedData.resize(uncompressedLen);
    bool status = snappy::RawUncompress(
        (const char*)compressedData.data(), compressedData.size(), (char*)&uncompressedData[0]);
    /// uncompress failed
    if (!status)
    {
        LOG(ERROR) << LOG_BADGE("SnappyCompressio") << LOG_DESC("uncompress failed");
        return 0;
    }
#if 0
    LOG(DEBUG) << LOG_BADGE("SnappyCompressio") << LOG_DESC("uncompress")
               << LOG_KV("org_len", uncompressedLen)
               << LOG_KV("compress_len", compressedData.size())
               << LOG_KV("ratio", (float)uncompressedLen / (float)compressedData.size())
               << LOG_KV("timecost", (utcTimeUs() - start_t));
#endif
    return uncompressedLen;
}
}  // namespace compress
}  // namespace dev
