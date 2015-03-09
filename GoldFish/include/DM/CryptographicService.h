/*
 * The base class of encrypt/decode service
 */

#ifndef CRYPTOGRAPHICSERVICE_H
#define CRYPTOGRAPHICSERVICE_H

#include <boost/shared_ptr.hpp>

#include "Config.h"

class CryptographicService
{
public:

    virtual ~CryptographicService();
    virtual STDSTR encrypt(STDSTR const&) = 0;
    virtual STDSTR decode(STDSTR const&) = 0;
};

typedef boost::shared_ptr<CryptographicService> CryptographicServicePtr;

#endif