

#include "sm3.h"
int SM3Hash::init(SM3_CTX* c)
{
    return ::SM3_Init(c);
}

int SM3Hash::update(SM3_CTX* c, const void* data, size_t len)
{
    return ::SM3_Update(c, data, len);
}

int SM3Hash::final(unsigned char* md, SM3_CTX* c)
{
    return ::SM3_Final(md, c);
}

unsigned char* SM3Hash::sm3(const unsigned char* d, size_t n, unsigned char* md)
{
    return ::SM3(d, n, md);
}

void SM3Hash::transForm(SM3_CTX* c, const unsigned char* data)
{
    ::SM3_Transform(c, data);
}

SM3Hash& SM3Hash::getInstance()
{
    static SM3Hash sm3;
    return sm3;
}