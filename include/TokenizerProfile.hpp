#pragma once
#include <vector>
#include "KoreanPos.hpp"

namespace OpenKorean {
struct TokenizerProfile {
    float tokenCount = 0.18f;
    float unknown = 0.3f;
    float wordCount = 0.3f;
    float freq = 0.2f;
    float unknownCoverage = 0.5f;
    float exactMatch = 0.5f;
    float allNoun = 0.1f;
    float unknownPosCount = 10.0f;
    float determinerPosCount = -0.01f;
    float exclamationPosCount = 0.01f;
    float initialPostPosition = 0.2f;
    float haVerb = 0.3f;
    float preferredPattern = 0.6f;
    std::vector<std::vector<KoreanPos::KoreanPosEnum>> preferredPatterns = { {KoreanPos::KoreanPosEnum::Noun, KoreanPos::KoreanPosEnum::Josa}, {KoreanPos::KoreanPosEnum::ProperNoun, KoreanPos::KoreanPosEnum::Josa} };
    std::vector<int> spaceGuide = std::vector<int>();
    float spaceGuidePenalty = 3.0f;
    float josaUnmatchedPenalty = 3.0f;

    TokenizerProfile() = default;
};
}