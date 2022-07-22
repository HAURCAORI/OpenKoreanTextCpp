#include "KoreanNormalizer.hpp"
#include <utility>

using namespace OpenKorean;
const std::wregex EXTENTED_KOREAN_REGEX = std::wregex(LR"(([ㄱ-ㅣ가-힣]+))");
const std::wregex KOREAN_TO_NORMALIZE_REGEX = std::wregex(LR"(([가-힣]+)(ㅋ+|ㅎ+|[ㅠㅜ]+))");
const std::wregex REPEATING_CHAR_REGEX = std::wregex(LR"((.)\1{3,}|[ㅠㅜ]{3,})");
const std::wregex REPEATING_2CHAR_REGEX = std::wregex(LR"((..)\1{2,})");
const std::wregex WHITESPACE_REGEX = std::wregex(LR"(\s+)");
const std::set<Char> CODA_N_EXCPETION = {L'은',L'는',L'운',L'인',L'텐',L'근',L'른',L'픈',L'닌',L'든',L'던'};


std::wstring KoreanNormalizer::normalizeCodaN(const std::wstring& chunk) {
    if(chunk.length() < 2) { return chunk; }

    std::wstring lastTwo = takeRight(chunk, 2);
    std::wstring last = takeRight(chunk);

    Char lastTwoHead = lastTwo[0];

    // Exception cases
    if(mKoreanDictionaryProvider.contain(KoreanPos::KoreanPosEnum::Noun, chunk) ||
    mKoreanDictionaryProvider.contain(KoreanPos::KoreanPosEnum::Conjunction, chunk) ||
    mKoreanDictionaryProvider.contain(KoreanPos::KoreanPosEnum::Adverb, chunk) ||
    mKoreanDictionaryProvider.contain(KoreanPos::KoreanPosEnum::Noun, lastTwo) ||
    lastTwoHead < L'가' || lastTwoHead > L'힣' ||
    CODA_N_EXCPETION.find(lastTwoHead) != CODA_N_EXCPETION.end()
    ) {
        return chunk;
    }

    //if(Predicates.find(KoreanTokenizer))
    return chunk;
}

/*
    초성체 사용 된 문장 복원 함수
*/
std::wstring KoreanNormalizer::normalizeEmotionAttachedChunk(const std::wstring& s, const std::wstring& toNormalize) {
    if(s.length() == 0) { return s; }
    std::wstring init = s.substr(0,s.length() - 1);
    HangulChar secondToLastDecomposed;
    if(init.length() > 0) {
        HangulChar hc = Hangul::decomposeHangul(init[init.length() - 1]);
        if(hc.coda == L' ') {
            secondToLastDecomposed = hc;
        }
    }
    HangulChar temp = Hangul::decomposeHangul(s[s.length() - 1]);
    if(temp.coda == L'ㅋ' || temp.coda == L'ㅎ') {
        // 갘ㅋㅋ -> 가
        return init + Hangul::composeHangul(temp.onset, temp.vowel);
    } else if(!secondToLastDecomposed.isNull() && temp.vowel == toNormalize[0] && Hangul::CODA_SET.find(temp.onset) != Hangul::CODA_SET.end()) {
        // 슬프뮤ㅠㅠ -> 슬픔
        return init.substr(0, init.length() - 1) + Hangul::composeHangul(secondToLastDecomposed.onset,secondToLastDecomposed.vowel,temp.onset);
    } else {
        return s;
    }
}

wstringMatchRet KoreanNormalizer::processNormalizationCandidate(wstringMatchArg match) {
    std::wstring chunk = match[1];
    std::wstring toNormalize = match[2];
    std::wstring normalizedChunk;
    if(mKoreanDictionaryProvider.contain(KoreanPos::KoreanPosEnum::Noun,chunk) || mKoreanDictionaryProvider.contain(KoreanPos::KoreanPosEnum::Eomi,takeRight(chunk)) || mKoreanDictionaryProvider.contain(KoreanPos::KoreanPosEnum::Eomi,takeRight(chunk,2))) {
        normalizedChunk = chunk;
    } else {
        normalizedChunk = normalizeEmotionAttachedChunk(chunk, toNormalize);
    }
    return normalizedChunk + toNormalize;
}
wstringMatchRet KoreanNormalizer::normalizeKoreanChunk(wstringMatchArg match) {
    // Normalize endings: 안됔ㅋㅋㅋ -> 안돼ㅋㅋ
    std::wstring endingNormalized = replaceAll(match[0], KOREAN_TO_NORMALIZE_REGEX, [&](wstringMatchArg match) { return processNormalizationCandidate(match); });

    // Normalize repeating chars: ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ -> ㅋㅋㅋ
    std::wstring exclamationNormalized = replaceAll(endingNormalized, REPEATING_CHAR_REGEX, [&](wstringMatchArg match) { return take(match[0], 3); });

    // Normalize repeating chars: 훌쩍훌쩍훌쩍훌쩍훌쩍훌쩍훌쩍훌쩍훌쩍훌쩍훌쩍훌쩍훌쩍 -> 훌쩍훌쩍
    std::wstring repeatingNormalized = replaceAll(exclamationNormalized, REPEATING_2CHAR_REGEX, [&](wstringMatchArg match) { return take(match[0], 4); });
    
    // Coda normalization (명사 + ㄴ 첨가 정규화): 소린가 -> 소리인가

    return repeatingNormalized;
}

std::wstring KoreanNormalizer::normalize(const std::wstring& input) {
    
    std::wstring output = replaceAll(input, EXTENTED_KOREAN_REGEX, [&](wstringMatchArg match) { return normalizeKoreanChunk(match); });
    

    
    //std::replace(input,EXTENTED_KOREAN_REGEX,normalizeKoreanChunk())
    return output;
}