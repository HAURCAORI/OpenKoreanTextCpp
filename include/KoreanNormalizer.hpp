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
    std::wstring normalizeCodaN(const std::wstring& chunk);
    //std::string processNormalizationCandidate(std::vector<std::string> m); //Match
    std::wstring normalizeEmotionAttachedChunk(const std::wstring& s, const std::wstring& toNormalize);

    public:
    KoreanNormalizer(KoreanDictionaryProvider& m) : mKoreanDictionaryProvider(std::ref(m)) {}
    
    std::wstring normalize(const std::wstring& input);

};

}