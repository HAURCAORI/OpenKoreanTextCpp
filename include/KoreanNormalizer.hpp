#pragma once
#include <string>
#include <vector>
#include "KoreanDictionaryProvider.hpp"
#include "StringProcess.hpp"

namespace OpenKorean {
//Segment
struct Segment {
    std::wstring text;
    std::vector<std::wstring> matchData;
};

//KoreanNormalizer
class KoreanNormalizer {
    private:
    KoreanDictionaryProvider& mKoreanDictionaryProvider;

    std::wstring processNormalizationCandidate(const std::wsmatch& match);
    std::wstring normalizeKoreanChunk(const std::wsmatch& match);
    //std::string normalizeKoreanChunk(const std::string& input);
    //std::string correctTypo(std::string chunk); //protected
    //std::string normalizeCodaN(std::string chunk); //protected
    //std::string processNormalizationCandidate(std::vector<std::string> m); //Match
    //std::string normalizeEmitionAttachedChunk(std::string s, std::string toNormalize);

    public:
    KoreanNormalizer(KoreanDictionaryProvider& m) : mKoreanDictionaryProvider(std::ref(m)) {}
    std::wstring normalize(const std::wstring& input);

};

}