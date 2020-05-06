

#include "AES.h"
#include "Exceptions.h"
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/sha.h>
#include <stdlib.h>
#include <string>


using namespace std;
using namespace dev;
using namespace dev::crypto;
using namespace std;

string dev::aesCBCEncrypt(const string& _plainData, const string& _key)
{
    string ivData(_key.substr(0, 16));
    string cipherData;
    CryptoPP::AES::Encryption aesEncryption((const unsigned char*)_key.data(), _key.size());
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(
        aesEncryption, (const unsigned char*)ivData.data());
    CryptoPP::StreamTransformationFilter stfEncryptor(
        cbcEncryption, new CryptoPP::StringSink(cipherData));
    stfEncryptor.Put((const unsigned char*)_plainData.data(), _plainData.size());
    stfEncryptor.MessageEnd();
    return cipherData;
}

string dev::aesCBCDecrypt(const string& _cypherData, const string& _key)
{
    string ivData(_key.substr(0, 16));
    // LOG(DEBUG)<<"AES DE TYPE....................";
    string decryptedData;
    CryptoPP::AES::Decryption aesDecryption((const unsigned char*)_key.data(), _key.size());
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(
        aesDecryption, (const unsigned char*)ivData.data());
    CryptoPP::StreamTransformationFilter stfDecryptor(
        cbcDecryption, new CryptoPP::StringSink(decryptedData));
    // stfDecryptor.Put( reinterpret_cast<const unsigned char*>( cipherData.c_str() ),cipherLen);
    stfDecryptor.Put((const unsigned char*)_cypherData.data(), _cypherData.size());
    stfDecryptor.MessageEnd();
    return decryptedData;
}

bytes dev::aesCBCEncrypt(bytesConstRef _plainData, bytesConstRef _key)
{
    bytesConstRef ivData = _key.cropped(0, 16);
    string cipherData;
    CryptoPP::AES::Encryption aesEncryption(_key.data(), _key.size());
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, ivData.data());
    CryptoPP::StreamTransformationFilter stfEncryptor(
        cbcEncryption, new CryptoPP::StringSink(cipherData));
    stfEncryptor.Put(_plainData.data(), _plainData.size());
    stfEncryptor.MessageEnd();
    return asBytes(cipherData);
}

bytes dev::aesCBCDecrypt(bytesConstRef _cypherData, bytesConstRef _key)
{
    bytes ivData = _key.cropped(0, 16).toBytes();
    // bytesConstRef ivData = _key.cropped(0, 16);
    // LOG(DEBUG)<<"AES DE TYPE....................";
    string decryptedData;
    CryptoPP::AES::Decryption aesDecryption(_key.data(), _key.size());
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, ref(ivData).data());
    CryptoPP::StreamTransformationFilter stfDecryptor(
        cbcDecryption, new CryptoPP::StringSink(decryptedData));
    // stfDecryptor.Put( reinterpret_cast<const unsigned char*>( cipherData.c_str() ),cipherLen);
    stfDecryptor.Put(_cypherData.data(), _cypherData.size());
    stfDecryptor.MessageEnd();
    return asBytes(decryptedData);
}
