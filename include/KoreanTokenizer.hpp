#pragma once
#include <map>
//#include "KoreanPos.hpp"
#include "KoreanToken.hpp"
#include "TokenizerProfile.hpp"
#include "KoreanStemmer.hpp"

namespace OpenKorean {

struct KoreanToken;

class KoreanTokenizer {
private:
    KoreanStemmer& mKoreanStemmer;

    static const int TOP_N_PER_STATE = 5;
    static const int MAX_TRACE_BACK = 8;
    static const std::map<std::wstring, KoreanPos::KoreanPosEnum> SequenceDefinition;

    static const std::vector<KoreanPosTrie> koreanPosTrie;
public:
    KoreanTokenizer(KoreanStemmer& m) : mKoreanStemmer(std::ref(m)) {}
    std::vector<KoreanToken> tokenize(const std::wstring& text, TokenizerProfile profile = TokenizerProfile());
};
}