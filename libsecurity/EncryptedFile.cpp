 
/**
 * @brief : Encrypt file
 * @author: jimmyshi, websterchen
 * @date: 2018-12-06
 */

#include "EncryptedFile.h"
#include <libconfig/GlobalConfigure.h>
#include <libdevcore/Base64.h>
#include <libdevcore/CommonIO.h>
#include <libdevcore/Exceptions.h>

using namespace std;
using namespace dev;

bytes EncryptedFile::decryptContents(const std::string& _filePath)
{
    bytes encFileBytes;
    bytes encFileBase64Bytes;
    bytes decFileBytes;
    try
    {
        LOG(DEBUG) << LOG_BADGE("ENCFILE") << LOG_DESC("Trying to read enc file")
                   << LOG_KV("file", _filePath);
        string encContextsStr = contentsString(_filePath);
        encFileBytes = fromHex(encContextsStr);
        LOG(DEBUG) << LOG_BADGE("ENCFILE") << LOG_DESC("Enc file contents")
                   << LOG_KV("string", encContextsStr) << LOG_KV("bytes", toHex(encFileBytes));

        bytes dataKey = asBytes(g_BCOSConfig.diskEncryption.dataKey);

        encFileBase64Bytes = aesCBCDecrypt(ref(encFileBytes), ref(dataKey));

        string decFileBytesBase64 = asString(encFileBase64Bytes);
        LOG(DEBUG) << "[ENCFILE] EncryptedFile Base64 key: " << decFileBytesBase64 << endl;
        decFileBytes = fromBase64(decFileBytesBase64);
    }
    catch (exception& e)
    {
        LOG(ERROR) << LOG_DESC("[ENCFILE] EncryptedFile error")
                   << LOG_KV("what", boost::diagnostic_information(e));
        BOOST_THROW_EXCEPTION(EncryptedFileError());
    }
    // LOG(DEBUG) << "[ENCFILE] Decrypt file [name/cipher/plain]: " << _filePath << "/"
    //           << toHex(encFileBytes) << "/" << toHex(decFileBytes) << endl;
    return decFileBytes;
}