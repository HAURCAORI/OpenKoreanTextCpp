#pragma once
#include "KoreanPos.hpp"
#include "Hangul.hpp"
#include "KoreanToken.hpp"
#include "TokenizerProfile.hpp"

#include <algorithm>

template <typename T>
std::vector<std::vector<T>> sliding(const std::vector<T>& vec, size_t window){
    if(vec.size() <= window) {
        return std::vector<std::vector<T>>(1, vec);
    }
    std::vector<std::vector<T>> ret;
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        if(it + window - 1 == vec.end()) { break; }
        ret.insert(ret.end(), std::vector<T>(it, it + window));
    }
    return ret;
}

template <typename Enumeration>
auto as_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

namespace OpenKorean {

class ParsedChunk {
private:
    static const std::set<KoreanPos::KoreanPosEnum> suffixes;
    static const std::set<KoreanPos::KoreanPosEnum> preferredBeforeHaVerb;
    static const std::set<std::wstring> josaCheck_1;
    static const std::set<std::wstring> josaCheck_2;

    std::vector<KoreanToken> m_posNodes;
    int m_words;
    TokenizerProfile m_profile;

    
    int countUnknowns;
    int countTokens;
    int isInitialPostPosition;
    int isExactMatch;
    int hasSpaceOutOfGuide;
    int isAllNouns;
    int isPreferredPattern;
    int isNounHa;
    
    int getUnknownCoverage;
    float getFreqScore;
    //int countPos;
    int josaMismatched;
    
    
public:
    float score;
    int posTieBreaker; // KoreanPos enum 순서로 결정

    ParsedChunk() = default;
    ParsedChunk(const std::vector<KoreanToken>& posNodes, int words, TokenizerProfile profile = TokenizerProfile()) : m_posNodes(posNodes), m_words(words), m_profile(profile) {
        countUnknowns = std::count_if(posNodes.begin(), posNodes.end(), [](const KoreanToken& token) { return token.unknown; });
        countTokens = posNodes.size();
        isInitialPostPosition = (suffixes.find(posNodes.front().pos) != suffixes.end()) ? 1 : 0;
        isExactMatch = (posNodes.size() == 1) ? 0 : 1;
        if(profile.spaceGuide.empty()) {
            hasSpaceOutOfGuide = 0;
        } else {
            std::vector<KoreanToken> filter;
            std::copy_if(posNodes.begin(), posNodes.end(), std::back_inserter(filter), [&](const KoreanToken& token){ return suffixes.find(token.pos) == suffixes.end(); });
            hasSpaceOutOfGuide = std::count_if(filter.begin(), filter.end(), [&](const KoreanToken& token) { return std::find(profile.spaceGuide.begin(), profile.spaceGuide.end(), token.offset) == profile.spaceGuide.end();} );
        }
        isAllNouns = (std::any_of(posNodes.begin(), posNodes.end(),
            [](const KoreanToken& token){ return token.pos != KoreanPos::KoreanPosEnum::Noun && token.pos != KoreanPos::KoreanPosEnum::ProperNoun;}
        )) ? 1 : 0;

        std::vector<KoreanPos::KoreanPosEnum> temp;
        std::transform(posNodes.begin(), posNodes.end(), temp.begin(), [](const KoreanToken& token) { return token.pos; });
        isPreferredPattern = (posNodes.size() == 2 && std::find(profile.preferredPatterns.begin(), profile.preferredPatterns.end(), temp) != profile.preferredPatterns.end()) ? 0 : 1;

        isNounHa = (posNodes.size() >= 2 
            && preferredBeforeHaVerb.find(posNodes.front().pos) != preferredBeforeHaVerb.end()
            && posNodes[1].pos == KoreanPos::KoreanPosEnum::Verb
            && ( posNodes[1].text.front() == L'하' || posNodes[1].text.front() == L'해' )
        ) ? 0 : 1;

        int sum_ptb = 0;
        for(auto it = posNodes.begin(); it != posNodes.end(); ++it) {
            sum_ptb += as_integer(it->pos);
        }
        posTieBreaker = sum_ptb;

        int sum = 0;
        for(auto it = posNodes.begin(); it != posNodes.end(); ++it) {
            if(it->unknown) {
                sum += it->text.length();
            }
        }
        getUnknownCoverage = sum;

        //getFreqScore;

        std::vector<std::vector<KoreanToken>> sld = sliding(posNodes,2);
        josaMismatched = (std::any_of(sld.begin(), sld.end(), [](const std::vector<KoreanToken>& tokenPair){ 
            if(tokenPair.front().pos == KoreanPos::KoreanPosEnum::Noun && tokenPair.back().pos == KoreanPos::KoreanPosEnum::Josa) {
                if(Hangul::hasCoda(tokenPair.front().text.back())) {
                    HangulChar nounEnding = Hangul::decomposeHangul(tokenPair.front().text.back());
                    return (nounEnding.coda != L'ㄹ' && tokenPair.back().text.front() == L'로') || (josaCheck_1.find(tokenPair.back().text) != josaCheck_1.end());
                } else {
                    return tokenPair.back().text.front() == L'으' || (josaCheck_2.find(tokenPair.back().text) != josaCheck_2.end());
                }
            } else {
                return false;
            }
         } )) ? 1 : 0;
        score = countTokens * profile.tokenCount +
            countUnknowns * profile.unknown +
            words * profile.wordCount +
            getUnknownCoverage * profile.unknownCoverage +
            getFreqScore * profile.freq +
            countPos(KoreanPos::KoreanPosEnum::Unknown) * profile.unknownPosCount +
            isExactMatch * profile.exactMatch +
            isAllNouns * profile.allNoun +
            isPreferredPattern * profile.preferredPattern +
            countPos(KoreanPos::KoreanPosEnum::Determiner) * profile.determinerPosCount +
            countPos(KoreanPos::KoreanPosEnum::Exclamation) * profile.exclamationPosCount +
            isInitialPostPosition * profile.initialPostPosition +
            isNounHa * profile.haVerb +
            hasSpaceOutOfGuide * profile.spaceGuidePenalty +
            josaMismatched * profile.josaUnmatchedPenalty;
    }

    int countPos(KoreanPos::KoreanPosEnum pos) {
        return std::count_if(m_posNodes.begin(), m_posNodes.end(), [&](const KoreanToken& token) { return token.pos == pos; });
    }

    ParsedChunk operator*(const ParsedChunk& rhs) {
        std::vector<KoreanToken> ret(this->m_posNodes.begin(), this->m_posNodes.end());
        ret.insert(ret.end(), rhs.m_posNodes.begin(), rhs.m_posNodes.end());
        return ParsedChunk(ret, this->m_words + rhs.m_words, this->m_profile);
    }

    inline std::vector<KoreanToken> posNodes() { return m_posNodes; }
};


struct CandidateParse {
    ParsedChunk parse;
    std::vector<KoreanPosTrie> curTrie;
    KoreanPos::KoreanPosEnum ending;
    CandidateParse() = default;
    CandidateParse(const ParsedChunk& p, const std::vector<KoreanPosTrie>& c, KoreanPos::KoreanPosEnum e) : parse(p), curTrie(c), ending(e) {}
};

}