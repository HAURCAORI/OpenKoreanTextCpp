#include "stdafx.h"

namespace OpenKorean {
//Segment
struct Segment {
    std::wstring text;
    std::vector<std::wstring> matchData;
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
    std::wstring normalize(const std::wstring& input);

};

}