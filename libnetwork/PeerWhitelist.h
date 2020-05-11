
#pragma once
#include <libdevcore/FixedHash.h>
#include <memory>
#include <set>
#include <string>
#include <vector>

using NodeID = dev::h512;
using NodeIDs = std::vector<NodeID>;

namespace dev
{
class PeerWhitelist : public std::enable_shared_from_this<PeerWhitelist>
{
public:
    using Ptr = std::shared_ptr<PeerWhitelist>;
    PeerWhitelist(std::vector<std::string> _strList, bool _enable = false);
    bool has(NodeID _peer) const;
    bool has(const std::string& _peer) const;
    void setEnable(bool _enable) { m_enable = _enable; }
    bool enable() const { return m_enable; }
    std::string dump(bool _isAbridged = false);

    static bool isNodeIDOk(NodeID _nodeID);
    static bool isNodeIDOk(const std::string& _nodeID);

private:
    bool m_enable = false;
    std::set<NodeID> m_whitelist;
};
}  // namespace dev