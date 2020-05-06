
#pragma once
#include <openssl/sm3.h>
class SM3Hash
{
public:
    int init(SM3_CTX* c);
    int update(SM3_CTX* c, const void* data, size_t len);
    int final(unsigned char* md, SM3_CTX* c);
    unsigned char* sm3(const unsigned char* d, size_t n, unsigned char* md);
    void transForm(SM3_CTX* c, const unsigned char* data);
    static SM3Hash& getInstance();
};