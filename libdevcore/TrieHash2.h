
#pragma once

#include <libdevcore/FixedHash.h>
#include <vector>

namespace dev
{
h256 getHash256(const std::vector<dev::bytes>& bytesCaches);

void getMerkleProof(const std::vector<dev::bytes>& bytesCaches,
    std::shared_ptr<std::map<std::string, std::vector<std::string>>> _parent2ChildList);

}  // namespace dev
