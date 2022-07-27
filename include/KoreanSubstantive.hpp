#pragma once
#include "Hangul.hpp"
#include "KoreanDictionaryProvider.hpp"

namespace OpenKorean {
class KoreanSubstantive {
private:
    static const std::set<Char> JOSA_HEAD_FOR_CODA;
    static const std::set<Char> JOSA_HEAD_FOR_NO_CODA;
    static const std::map<int, Char> NUMBER_CHARS;
    static const std::map<int, Char> NUMBER_LAST_CHARS;
    KoreanDictionaryProvider& mKoreanDictionaryProvider;

public:
    KoreanSubstantive(KoreanDictionaryProvider& m) : mKoreanDictionaryProvider(std::ref(m)) {}
    static bool isJosaAttachable(Char prevChar, Char headChar);
    
    bool isName(const std::wstring& chunk);
};
}