#pragma once
#include <set>
#include "KoreanPos.hpp"
#include "KoreanTokenizer.hpp"

namespace OpenKorean {
class KoreanStemmer {
private:
    static const std::set<KoreanPos::KoreanPosEnum> Endings;
    static const std::set<KoreanPos::KoreanPosEnum> Predicates;
    static const std::set<std::wstring> EndingsForNouns;

public:
    static std::vector<KoreanToken> stem(const std::vector<KoreanToken>& tokens);

};
}