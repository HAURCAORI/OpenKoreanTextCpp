#pragma once
#include <KoreanNormalizer.hpp>

namespace OpenKorean {
class OpenKoreanTextProcessor {
private:
    KoreanNormalizer mKoreanNormalizer;

public:
    inline std::string normalize(std::string text) {
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