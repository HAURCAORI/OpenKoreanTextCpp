#include "KoreanTokenizer.hpp"
#include "ParsedChunk.hpp"


using namespace OpenKorean;

inline std::wstring substrPos(const std::wstring& str, size_t start, size_t end) {
  if(end < start) { return str; }
  if(start > str.length()) { return L""; }
  return str.substr(start, end - start);
}

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

std::vector<std::vector<KoreanToken>> KoreanTokenizer::parseKoreanChunk(KoreanToken chunk, TokenizerProfile profile, int topN) {
    auto candidates = findTopCandidates(chunk, profile);
    return ((signed) candidates.size() < topN ) ? candidates : std::vector<std::vector<KoreanToken>>(candidates.begin(),  candidates.begin() + topN);
}

std::vector<std::vector<KoreanToken>> KoreanTokenizer::findTopCandidates(KoreanToken chunk, TokenizerProfile profile) {
    
    std::vector<std::vector<KoreanToken>> directMatch = findDirectMatch(chunk);
    std::unordered_map<int, std::vector<CandidateParse>> solutions;
    std::vector<KoreanToken> empty;
    solutions.insert(std::make_pair(0,std::vector<CandidateParse>(1, CandidateParse(ParsedChunk(empty, 1, profile), koreanPosTrie, KoreanPos::KoreanPosEnum::Null))));

    for(int end = 1; end <= chunk.length; ++end) {
        for(int start = end - 1; start >= std::max(end-MAX_TRACE_BACK,0); --start) {
            std::wstring word = substrPos(chunk.text, start, end);
            
            removeUnusedSolutions(start,end, solutions);

            std::vector<CandidateParse> curSolutions = solutions[start];
            std::vector<CandidateParse> candidates;
            
            
            std::transform(curSolutions.begin(),curSolutions.end(),candidates.begin(), [&](CandidateParse& solution) {
                
                std::vector<PossibleTrie> possiblePoses;
                std::transform(solution.curTrie.begin(), solution.curTrie.end(), possiblePoses.begin(), [](KoreanPosTrie& t) {return PossibleTrie(t,0); });
                if(solution.ending != KoreanPos::KoreanPosEnum::Null) {
                    std::transform(koreanPosTrie.begin(), koreanPosTrie.end(), std::back_inserter(possiblePoses), [](KoreanPosTrie& t) {return PossibleTrie(t,1); });
                }
                std::vector<PossibleTrie> filtered;
                
                std::copy_if(possiblePoses.begin(), possiblePoses.end(), filtered.begin(), [&](PossibleTrie& t) {
                    return (t.curTrie.curPos == KoreanPos::KoreanPosEnum::Noun) || mKoreanDictionaryProvider.contain(t.curTrie.curPos, word);
                });
                /*
                for(auto it = filtered.begin(); it != filtered.end(); ++it) {
                    ParsedChunk candidateToAdd;
                    if(it->curTrie.curPos == KoreanPos::KoreanPosEnum::Noun && !mKoreanDictionaryProvider.contain(KoreanPos::KoreanPosEnum::Noun, word)) {
                        //bool isWordName = 
                    }

                }
                */
               
                //possiblePoses

                return solution;
            });
            
        }
    }
    

    return std::vector<std::vector<KoreanToken>>();
}

template<typename T>
void KoreanTokenizer::removeUnusedSolutions(int start, int end, std::unordered_map<int,T>& solutions) {
    if(end > MAX_TRACE_BACK && start + 1 == end) {
        solutions.erase(end - MAX_TRACE_BACK -1);
    }
}


std::vector<std::vector<KoreanToken>> KoreanTokenizer::findDirectMatch(KoreanToken chunk) {
    auto& dic = mKoreanDictionaryProvider.getDictionaries();
    for(auto it = dic.begin(); it != dic.end(); ++it) {
        if(it->second.find(chunk.text) != it->second.end()) {
            return std::vector<std::vector<KoreanToken>>(1,std::vector<KoreanToken>(1, {chunk.text, it->first, chunk.offset, chunk.length}));
        }
    }
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