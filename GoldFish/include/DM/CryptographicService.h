#ifndef CRYPTOGRAPHICSERVICE_H
#define CRYPTOGRAPHICSERVICE_H

#include "Config.h"

class CryptographicService
{
public:

    virtual int encrypt(Token&) = 0;
    virtual int decode(Token&) = 0;
};

#endif