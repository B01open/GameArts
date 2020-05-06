

#pragma once

#include <libethcore/EVMSchedule.h>
#include <atomic>
#include <string>
namespace dev
{
enum VERSION : uint32_t
{
    RC1_VERSION = 1,
    RC2_VERSION = 2,
    RC3_VERSION = 3,
    V2_0_0 = 0x02000000,
    V2_1_0 = 0x02010000,
    V2_2_0 = 0x02020000,
    V2_3_0 = 0x02030000,
};

enum ProtocolVersion : uint32_t
{
    v1 = 1,
    v2 = 2,
    // TODO: update SDK protocol to V3 after sdk-2.1.1 released
    v3 = 3,
    maxVersion = v3,
    minVersion = v1,
};

class GlobalConfigure
{
public:
    static GlobalConfigure& instance()
    {
        static GlobalConfigure ins;
        return ins;
    }
    GlobalConfigure() : shouldExit(false) {}
    VERSION const& version() const { return m_version; }
    void setCompress(bool const& compress) { m_compress = compress; }

    bool compressEnabled() const { return m_compress; }

    void setChainId(int64_t _chainId) { m_chainId = _chainId; }
    int64_t chainId() const { return m_chainId; }

    void setSupportedVersion(std::string const& _supportedVersion, VERSION _versionNumber)
    {
        m_supportedVersion = _supportedVersion;
        m_version = _versionNumber;
    }
    std::string const& supportedVersion() { return m_supportedVersion; }

    void setEVMSchedule(dev::eth::EVMSchedule const& _schedule) { m_evmSchedule = _schedule; }
    dev::eth::EVMSchedule const& evmSchedule() const { return m_evmSchedule; }

    struct DiskEncryption
    {
        bool enable = false;
        std::string keyCenterIP;
        int keyCenterPort;
        std::string cipherDataKey;
        std::string dataKey;
    } diskEncryption;

    struct Binary
    {
        std::string version;
        std::string buildTime;
        std::string buildInfo;
        std::string gitBranch;
        std::string gitCommitHash;
    } binaryInfo;

    /// default block time
    const unsigned c_intervalBlockTime = 1000;
    /// omit empty block or not
    const bool c_omitEmptyBlock = true;
    /// default blockLimit
    const unsigned c_blockLimit = 1000;
    /// default compress threshold: 1KB
    const uint64_t c_compressThreshold = 1024;
    const uint64_t c_binaryLogSize = 128 * 1024 * 1024;

    std::atomic_bool shouldExit;

private:
    VERSION m_version = RC3_VERSION;
    bool m_compress;
    int64_t m_chainId = 1;
    std::string m_supportedVersion;
    dev::eth::EVMSchedule m_evmSchedule = dev::eth::DefaultSchedule;
};

#define g_BCOSConfig GlobalConfigure::instance()

}  // namespace dev