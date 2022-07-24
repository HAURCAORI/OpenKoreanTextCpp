#pragma once
#include "KoreanPos.hpp"
#include "KoreanToken.hpp"
#include "TokenizerProfile.hpp"

#include <algorithm>

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

    const std::vector<KoreanToken> m_posNodes;
    const int m_words;
    const TokenizerProfile m_profile;

    float score;
    int countUnknowns;
    int countTokens;
    int isInitializePosition;
    int isExactMatch;
    int hasSpaceOutOfGuide;
    int isAllNouns;
    int isPreferredPattern;
    int isNounHa;
    int posTieBreaker; // KoreanPos enum 순서로 결정
    int getUnknownCoverage;
    float getFreqScore;
    //int countPos;
    int josaMismatched;
    
    
public:
    ParsedChunk(const std::vector<KoreanToken>& posNodes, int words, TokenizerProfile profile = TokenizerProfile()) : m_posNodes(posNodes), m_words(words), m_profile(profile) {
        countUnknowns = std::count_if(posNodes.begin(), posNodes.end(), [](const KoreanToken& token) { return token.unknown; });
        countTokens = posNodes.size();
        isInitializePosition = (suffixes.find(posNodes.front().pos) != suffixes.end()) ? 1 : 0;
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

        

        //score = 
    }

    int countPos(KoreanPos::KoreanPosEnum pos) {
        return std::count_if(m_posNodes.begin(), m_posNodes.end(), [&](const KoreanToken& token) { return token.pos == pos; });
    }

    ParsedChunk operator*(const ParsedChunk& rhs) {
        std::vector<KoreanToken> ret(this->m_posNodes.begin(), this->m_posNodes.end());
        ret.insert(ret.end(), rhs.m_posNodes.begin(), rhs.m_posNodes.end());
        return ParsedChunk(ret, this->m_words + rhs.m_words, this->m_profile);
    }
};



}