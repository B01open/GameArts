 
/**
 * @brief : Encrypt file
 * @author: jimmyshi, websterchen
 * @date: 2018-12-06
 */

#pragma once
#include "Common.h"
#include <libdevcore/Common.h>
#include <libdevcrypto/AES.h>
#include <memory>

namespace dev
{
class EncryptedFile
{
public:
    static bytes decryptContents(const std::string& _filePath);
};


}  // namespace dev