#pragma once
#include "KoreanNormalizer.hpp"
#include "KoreanDictionaryProvider.hpp"
#include "KoreanStemmer.hpp"
#include "KoreanTokenizer.hpp"
namespace OpenKorean {
class OpenKoreanTextProcessor {
private:
    KoreanDictionaryProvider mKoreanDictionaryProvider;
    KoreanNormalizer mKoreanNormalizer;
    KoreanStemmer mKoreanStemmer;
    KoreanTokenizer mKoreanTokenizer;
public:
    OpenKoreanTextProcessor() : mKoreanDictionaryProvider(), mKoreanNormalizer(mKoreanDictionaryProvider), mKoreanStemmer(mKoreanDictionaryProvider), mKoreanTokenizer(mKoreanDictionaryProvider, mKoreanStemmer) {}
    
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