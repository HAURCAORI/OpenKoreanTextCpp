#include "KoreanNormalizer.hpp"
#include "StringProcess.hpp"


using namespace OpenKorean;
const std::wregex EXTENTED_KOREAN_REGEX = std::wregex(LR"(([ㄱ-ㅣ가-힣]+))");
const std::wregex KOREAN_TO_NORMALIZE_REGEX = std::wregex(LR"(([가-힣]+)(ㅋ+|ㅎ+|[ㅠㅜ]+))");
const std::wregex REPEATING_CHAR_REGEX = std::wregex(LR"((.)\1{3,}|[ㅠㅜ]{3,})");
const std::wregex REPEATING_2CHAR_REGEX = std::wregex(LR"((..)\1{2,})");
const std::wregex WHITESPACE_REGEX = std::wregex(LR"(\s+)");
const std::vector<std::wstring> CODA_N_EXCPETION = {L"은",L"는",L"운",L"인",L"텐",L"근",L"른",L"픈",L"닌",L"든",L"던"};

static wstringMatchRet processNormalizationCandidate(wstringMatchArg match) {
    std::wstring chunk = match[1];
    std::wstring toNormalize = match[2];
        
    //std::wstring normalizedChunk
    return chunk;
}
static wstringMatchRet normalizeKoreanChunk(wstringMatchArg match) {
    std::wstring output = replaceAll(match[0],KOREAN_TO_NORMALIZE_REGEX,processNormalizationCandidate);
    return output;
}

std::wstring KoreanNormalizer::normalize(const std::wstring& input) {
    std::wstring output = replaceAll(input,EXTENTED_KOREAN_REGEX, normalizeKoreanChunk);
    //std::cout << output << std::endl;
    //std::replace(input,EXTENTED_KOREAN_REGEX,normalizeKoreanChunk())
    return output;
}