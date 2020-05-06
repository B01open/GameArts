
#include "sm4.h"
#include <cstring>

int SM4::setKey(const unsigned char* userKey, size_t length)
{
    return ::SM4_set_key(userKey, length, &key);
}

void SM4::encrypt(const unsigned char* in, unsigned char* out)
{
    ::SM4_encrypt(in, out, &key);
}

void SM4::decrypt(const unsigned char* in, unsigned char* out)
{
    ::SM4_decrypt(in, out, &key);
}

void SM4::cbcEncrypt(
    const unsigned char* in, unsigned char* out, size_t length, unsigned char* ivec, const int enc)
{
    unsigned char* iv = (unsigned char*)malloc(16);
    std::memcpy(iv, ivec, 16);
    ::SM4_cbc_encrypt(in, out, length, &key, iv, enc);
    free(iv);
}

SM4& SM4::getInstance()
{
    static SM4 sm4;
    return sm4;
}