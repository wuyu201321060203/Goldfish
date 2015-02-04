/************************************************************************
** 本例采用：
** 3des-ecb加密方式；
** 24位密钥，不足24位的右补0x00；
** 加密内容8位补齐，补齐方式为：少1位补一个0x01,少2位补两个0x02,...
** 本身已8位对齐的，后面补八个0x08。
************************************************************************/

#ifndef DESECBSERVICE_H
#define DESECBSERVICE_H

#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>
#include <array>

#include "Config.h"
#include "CryptographicService.h"

class DesEcbService : public CryptographicService
{
public:

    DesEcbService();
    virtual STDSTR encrypt(STDSTR const&);
    virtual STDSTR decode(STDSTR const&);

private:

    std::array<DES_key_schedule , 3> _keyArray;

private:

    void generateKeyArray();
    void strCompletion(STDSTR&);
    STDSTR action(STDSTR const& , int);
};

#endif