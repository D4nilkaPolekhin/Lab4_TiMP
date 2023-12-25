/** @file
* @author Полехин Даниил
* @version 1.0
* @date 20.12.2023
* @warning Тренировочная работа
* @brief CPP файл для модуля шифрования методом Гронсфельда
*/
#include "modAlphaCipher.h"

std::wstring modAlphaCipher::toValidtext(const std::wstring& s, std::string obj)
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    if (s.empty())
        throw cipher_error("Empty "+obj);
    std::wstring tmp(s);
    std::string st = converter.to_bytes(s);
    obj[0]=toupper(obj[0]);
    for (auto & c:tmp) {
        if (!is_rus(c))
            throw cipher_error(std::string(obj+" has invalid symbols: ")+st);
        if (is_low_rus(c)!=-1)
            c = numAlpha[is_low_rus(c)];
    }
    return tmp;
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::wstring text(open_text);
    std::wstring valid_text=toValidtext(text, "string");
    std::vector<int> work = convert(valid_text);
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::wstring text(cipher_text);
    std::wstring valid_text=toValidtext(text, "string");
    std::vector<int> work = convert(valid_text);
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for(auto c:s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for(auto i:v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

bool modAlphaCipher::is_rus(wchar_t wch)
{
    std::wstring alf=lnumAlpha+numAlpha;
    for (uint i=0; i<alf.length(); i++) {
        if (wch == alf[i])
            return true;
    }
    return false;
}
int modAlphaCipher::is_low_rus(wchar_t wch)
{
    for (uint i=0; i<lnumAlpha.length(); i++) {
        if (wch == lnumAlpha[i])
            return i;
    }
    return -1;
}
