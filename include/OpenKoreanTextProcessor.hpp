#pragma once
#include "KoreanNormalizer.hpp"
#include "KoreanDictionaryProvider.hpp"

namespace OpenKorean {
class OpenKoreanTextProcessor {
private:
    KoreanDictionaryProvider mKoreanDictionaryProvider;
    KoreanNormalizer mKoreanNormalizer;

public:
    OpenKoreanTextProcessor() : mKoreanDictionaryProvider(), mKoreanNormalizer(mKoreanDictionaryProvider) {}
    
    inline std::wstring normalize(std::wstring text) {
        return mKoreanNormalizer.normalize(text);
    }

    KoreanNormalizer* getNormalizer() {
        return &mKoreanNormalizer;
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