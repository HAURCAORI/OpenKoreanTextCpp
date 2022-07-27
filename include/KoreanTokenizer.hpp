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
    KoreanDictionaryProvider& mKoreanDictionaryProvider;
    KoreanStemmer& mKoreanStemmer;

    static const int TOP_N_PER_STATE = 5;
    static const int MAX_TRACE_BACK = 8;
    static const std::map<std::wstring, KoreanPos::KoreanPosEnum> SequenceDefinition;

    std::vector<KoreanPosTrie> koreanPosTrie;

    std::vector<std::vector<KoreanToken>> parseKoreanChunk(KoreanToken chunk, TokenizerProfile profile = TokenizerProfile(), int topN = 1);
    std::vector<std::vector<KoreanToken>> findTopCandidates(KoreanToken chunk, TokenizerProfile profile);
    
    template<typename T>
    void removeUnusedSolutions(int start, int end, std::unordered_map<int,T>& solutions);
    std::vector<std::vector<KoreanToken>> findDirectMatch(KoreanToken chunk);

public:
    KoreanTokenizer(KoreanDictionaryProvider& md, KoreanStemmer& ms) :  mKoreanDictionaryProvider(std::ref(md)), mKoreanStemmer(std::ref(ms)) {
        koreanPosTrie = KoreanPos::getTrie(KoreanTokenizer::SequenceDefinition);
    }
    std::vector<KoreanToken> tokenize(const std::wstring& text, TokenizerProfile profile = TokenizerProfile());
    std::vector<std::vector<std::vector<KoreanToken>>> tokenizeTopN(const std::wstring& text, int topN = 1, TokenizerProfile profile = TokenizerProfile());
};
}