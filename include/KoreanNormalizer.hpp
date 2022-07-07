#pragma once
#include "stdafx.h"

namespace OpenKorean {
//Segment
struct Segment {
    std::string text;
    std::vector<std::string> matchData;
};

//KoreanNormalizer
class KoreanNormalizer {
    private:
    //std::string normalizeKoreanChunk(const std::string& input);
    //std::string correctTypo(std::string chunk); //protected
    //std::string normalizeCodaN(std::string chunk); //protected
    //std::string processNormalizationCandidate(std::vector<std::string> m); //Match
    //std::string normalizeEmitionAttachedChunk(std::string s, std::string toNormalize);

    public:
    std::string normalize(const std::string& input);

};

}