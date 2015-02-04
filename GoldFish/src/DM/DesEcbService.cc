#include <stdlib.h>
#include <string.h>

#include <DM/DesEcbService.h>
#include <Exception/ParameterException.h>

using namespace OOzdb;

DesEcbService::DesEcbService()
{
    generateKeyArray();
}

STDSTR DesEcbService::encrypt(STDSTR const& tokenStr)
{
    return action(tokenStr , ENCODE);
}

STDSTR DesEcbService::decode(STDSTR const& tokenStr)
{
    return action(tokenStr , DECODE);
}

void DesEcbService::generateKeyArray()
{
    STDSTR originKey(DES_KEY);
    int paddedBytes = LEN_OF_KEY - originKey.length();
    if(0 > paddedBytes)
        THROW(ParameterException , "paddedBytes cannot be negative");
    STDSTR stdKey(originKey);
    stdKey.append(paddedBytes , 0x00);
    unsigned char blockKey[9];
    unsigned char const* key = (unsigned char const*)(stdKey.c_str());
    memset(blockKey , 0 , sizeof(blockKey));
    memcpy(blockKey , key + 0 , 8);
    DES_set_key_unchecked((const_DES_cblock*)blockKey , &_keyArray.at(0));
    memcpy(blockKey , key + 8 , 8);
    DES_set_key_unchecked((const_DES_cblock*)blockKey , &_keyArray.at(1));
    memcpy(blockKey , key + 16 , 8);
    DES_set_key_unchecked((const_DES_cblock*)blockKey , &_keyArray.at(2));
}

void DesEcbService::strCompletion(STDSTR& data)
{
    int dataLen = data.length();
    int dataRest = dataLen % 8;
    char paddedChar = 8 - dataRest;
    data.append(8 - dataRest , paddedChar);
}

STDSTR DesEcbService::action(STDSTR const& str , int option)
{
    STDSTR tokenStr(str);
    int enc = DES_DECRYPT;
    if(ENCODE == option)
    {
        strCompletion(tokenStr);
        enc = DES_ENCRYPT;
    }
    int length = tokenStr.length();
    int times = length / 8;
    unsigned char tmp[8];
    unsigned char in[8];
    unsigned char const* src = (unsigned char const*)(tokenStr.c_str());
    char dst[length + 1];
    dst[length] = '\0';
    for(int i = 0 ; i != times ; ++i)
    {
        memset(tmp , 0 , 8);
        memset(in , 0 , 8);
        memcpy(tmp , src + 8 * i , 8);
        DES_ecb3_encrypt((const_DES_cblock*)tmp , (DES_cblock*)in,
            &_keyArray.at(0) , &_keyArray.at(1) , &_keyArray.at(2) , enc);
        memcpy(dst + 8 * i , in , 8);
    }
    return STDSTR(dst);
}