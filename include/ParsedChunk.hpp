#pragma once
#include "KoreanPos.hpp"
#include "KoreanToken.hpp"
#include "TokenizerProfile.hpp"

#include <algorithm>

namespace OpenKorean {
class ParsedChunk {
private:
    static const std::set<KoreanPos::KoreanPosEnum> suffixes;
    static const std::set<KoreanPos::KoreanPosEnum> preferredBeforeHaVerb;

    float score;
    int countUnknowns;
    int countTokens;
    int isInitializePosition;
    int isExactMatch;
    int hasSpaceOutOfGuide;
    int isAllNouns;
    int isPreferredPattern;
    int isNounHa;
    int posTieBreaker;
    int getUnknownCoverage;

public:
    ParsedChunk(const std::vector<KoreanToken>& posNodes, int words, TokenizerProfile profile = TokenizerProfile()) {
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

        //posTieBreaker = 

        //score = 
    }

};
}