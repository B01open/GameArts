

#pragma once

#include "Common.h"

namespace dev
{
DEV_SIMPLE_EXCEPTION(AESKeyLengthError);
bytes aesCBCEncrypt(bytesConstRef _plainData, bytesConstRef _key);
bytes aesCBCDecrypt(bytesConstRef _cypherData, bytesConstRef _key);
std::string aesCBCEncrypt(const std::string& _plainData, const std::string& _key);
std::string aesCBCDecrypt(const std::string& _cypherData, const std::string& _key);
}  // namespace dev
