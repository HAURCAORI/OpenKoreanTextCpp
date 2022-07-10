#pragma once
#include "KoreanNormalizer.hpp"
#include "KoreanDictionaryProvider.hpp"

namespace OpenKorean {
class OpenKoreanTextProcessor {
private:
    KoreanNormalizer mKoreanNormalizer;
    KoreanDictionaryProvider mKoreanDictionaryProvider;

public:
    OpenKoreanTextProcessor() = default;
    inline std::wstring normalize(std::wstring text) {
        return mKoreanNormalizer.normalize(text);
    }
    /*
    inline std::vector<KoreanToken> tokenize(std::string text) {
        return mKoreanTokenizer.tokenize(text);   
    }
    inline std::vector<KoreanToken> tokenize(std::string text, TokenizerProfile profile) {
        return mKoreanTokenizer.tokenize(text,profile); 
    }
    */
};
}