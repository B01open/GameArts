
#pragma once
#include <openssl/sm4.h>
class SM4
{
public:
    int setKey(const unsigned char* userKey, size_t length);
    void encrypt(const unsigned char* in, unsigned char* out);
    void decrypt(const unsigned char* in, unsigned char* out);
    void cbcEncrypt(const unsigned char* in, unsigned char* out, size_t length, unsigned char* ivec,
        const int enc);

    static SM4& getInstance();

private:
    SM4_KEY key;
};