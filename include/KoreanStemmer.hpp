#pragma once
#include <set>
#include "KoreanPos.hpp"
#include "KoreanToken.hpp"
#include "KoreanDictionaryProvider.hpp"

namespace OpenKorean {
class KoreanStemmer {
private:
    KoreanDictionaryProvider& mKoreanDictionaryProvider;

    static const std::set<KoreanPos::KoreanPosEnum> Endings;
    static const std::set<KoreanPos::KoreanPosEnum> Predicates;
    static const std::set<std::wstring> EndingsForNouns;

public:
    KoreanStemmer(KoreanDictionaryProvider& m) : mKoreanDictionaryProvider(std::ref(m)) {}
    std::vector<KoreanToken> stem(const std::vector<KoreanToken>& tokens);
};
}