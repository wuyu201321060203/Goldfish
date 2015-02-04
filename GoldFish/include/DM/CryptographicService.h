#ifndef CRYPTOGRAPHICSERVICE_H
#define CRYPTOGRAPHICSERVICE_H

#include "Config.h"

class CryptographicService
{
public:

    virtual STDSTR encrypt(STDSTR const&) = 0;
    virtual STDSTR decode(STDSTR const&) = 0;
};

#endif