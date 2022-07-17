#include "KoreanNormalizer.hpp"


using namespace OpenKorean;
const std::wregex EXTENTED_KOREAN_REGEX = std::wregex(LR"(([ㄱ-ㅣ가-힣]+))");
const std::wregex KOREAN_TO_NORMALIZE_REGEX = std::wregex(LR"(([가-힣]+)(ㅋ+|ㅎ+|[ㅠㅜ]+))");
const std::wregex REPEATING_CHAR_REGEX = std::wregex(LR"((.)\1{3,}|[ㅠㅜ]{3,})");
const std::wregex REPEATING_2CHAR_REGEX = std::wregex(LR"((..)\1{2,})");
const std::wregex WHITESPACE_REGEX = std::wregex(LR"(\s+)");
const std::vector<std::wstring> CODA_N_EXCPETION = {L"은",L"는",L"운",L"인",L"텐",L"근",L"른",L"픈",L"닌",L"든",L"던"};

wstringMatchRet KoreanNormalizer::processNormalizationCandidate(wstringMatchArg match) {
    std::wstring chunk = match[1];
    std::wstring toNormalize = match[2];
    if(mKoreanDictionaryProvider.contain(KoreanPos::Noun, L"사과")) {
        return chunk + toNormalize;
    }
    //std::wstring normalizedChunk
    return chunk;
}
wstringMatchRet KoreanNormalizer::normalizeKoreanChunk(wstringMatchArg match) {
    std::wstring output = replaceAll(match[0],KOREAN_TO_NORMALIZE_REGEX, [&](wstringMatchArg match) { return processNormalizationCandidate(match); });
    return output;
}

std::wstring KoreanNormalizer::normalize(const std::wstring& input) {
    // Normalize endings: 안됔ㅋㅋㅋ -> 안돼ㅋㅋ
    std::wstring output = replaceAll(input,EXTENTED_KOREAN_REGEX, [&](wstringMatchArg match) { return normalizeKoreanChunk(match); });
    //std::replace(input,EXTENTED_KOREAN_REGEX,normalizeKoreanChunk())
    return output;
}