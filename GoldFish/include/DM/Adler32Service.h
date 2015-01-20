#ifndef ADLER32_H
#define ADLER32_H

#include "CryptographicService.h"

class Adler32Service : public CryptographicService
{
public:

    int encrypt(Token& token);
    int decode(Token& token);
};

#endif