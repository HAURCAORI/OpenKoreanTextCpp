#pragma once
#include "Hangul.hpp"
#include "KoreanDictionaryProvider.hpp"
#include "KoreanToken.hpp"

namespace OpenKorean {
class KoreanSubstantive {
private:
    static const std::set<Char> JOSA_HEAD_FOR_CODA;
    static const std::set<Char> JOSA_HEAD_FOR_NO_CODA;
    static const std::set<Char> NUMBER_CHARS;
    static const std::set<Char> NUMBER_LAST_CHARS;
    KoreanDictionaryProvider& mKoreanDictionaryProvider;

public:
    KoreanSubstantive(KoreanDictionaryProvider& m) : mKoreanDictionaryProvider(std::ref(m)) {}
    static bool isJosaAttachable(Char prevChar, Char headChar);
    static bool isKoreanNumber(const std::wstring& chunk);
    
    bool isName(const std::wstring& chunk);
    bool isKoreanNameVariation(const std::wstring& chunk);
    std::vector<KoreanToken> collapseNouns(const std::vector<KoreanToken>& posNodes);
};
}