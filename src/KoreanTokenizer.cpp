#include "KoreanTokenizer.hpp"

using namespace OpenKorean;

const std::map<std::wstring, KoreanPos::KoreanPosEnum> KoreanTokenizer::SequenceDefinition = {
    // Substantive
    {L"D0m*N1s0j0", KoreanPos::KoreanPosEnum::Noun},
    // Predicate 초기뻐하다, 와주세요, 초기뻤었고, 추첨하다, 구경하기힘들다, 기뻐하는, 기쁜, 추첨해서, 좋아하다, 걸려있을
    {L"v*V1r*e0", KoreanPos::KoreanPosEnum::Verb},
    {L"v*J1r*e0", KoreanPos::KoreanPosEnum::Adjective},
    // Modifier 부사
    {L"A1", KoreanPos::KoreanPosEnum::Adverb},
    // Standalone
    {L"C1", KoreanPos::KoreanPosEnum::Conjunction},
    {L"E+", KoreanPos::KoreanPosEnum::Exclamation},
    {L"j1", KoreanPos::KoreanPosEnum::Josa}
};

const std::vector<KoreanPosTrie> KoreanTokenizer::koreanPosTrie = KoreanPos::getTrie(KoreanTokenizer::SequenceDefinition);

std::vector<std::vector<KoreanToken>> KoreanTokenizer::parseKoreanChunk(KoreanToken chunk, TokenizerProfile profile, int topN) {
    auto candidates = findTopCandidates(chunk, profile);
    return ((signed) candidates.size() < topN ) ? candidates : std::vector<std::vector<KoreanToken>>(candidates.begin(),  candidates.begin() + topN);
}

std::vector<std::vector<KoreanToken>> KoreanTokenizer::findTopCandidates(KoreanToken chunk, TokenizerProfile profile) {
    return std::vector<std::vector<KoreanToken>>();
}

std::vector<std::vector<KoreanToken>> KoreanTokenizer::findDirectMatch(KoreanToken chunk) {
    
    return std::vector<std::vector<KoreanToken>>();
}

std::vector<KoreanToken> KoreanTokenizer::tokenize(const std::wstring& text, TokenizerProfile profile) {
    //std::vector<std::vector<std::vector<KoreanToken>>> temp = tokenizeTopN(text, 1, profile);
    std::vector<KoreanToken> tokenized;

    return mKoreanStemmer.stem(tokenized);
}

std::vector<std::vector<std::vector<KoreanToken>>> KoreanTokenizer::tokenizeTopN(const std::wstring& text, int topN, TokenizerProfile profile) {
    
    return std::vector<std::vector<std::vector<KoreanToken>>>();
}