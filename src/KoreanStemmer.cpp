#include "KoreanStemmer.hpp"
#include <algorithm>

using namespace OpenKorean;

template<typename T>
std::vector<T> operator*(const std::vector<T>& lhs, const std::vector<T>& rhs) {
    std::vector<T> temp;
    temp.insert(temp.begin(), lhs.begin(), lhs.end());
    temp.insert(temp.begin(), rhs.begin(), rhs.end());
    return temp;
}

const std::set<KoreanPos::KoreanPosEnum> KoreanStemmer::Endings = { KoreanPos::KoreanPosEnum::Eomi, KoreanPos::KoreanPosEnum::PreEomi };
const std::set<KoreanPos::KoreanPosEnum> KoreanStemmer::Predicates = { KoreanPos::KoreanPosEnum::Verb, KoreanPos::KoreanPosEnum::Adjective };
const std::set<std::wstring> KoreanStemmer::EndingsForNouns = { L"하다", L"되다", L"없다" };

std::vector<KoreanToken> KoreanStemmer::stem(const std::vector<KoreanToken>& tokens) {
    bool exist = false;
    for(auto it = tokens.begin(); it != tokens.end(); ++it){
        if(it->pos == KoreanPos::KoreanPosEnum::Verb || it->pos == KoreanPos::KoreanPosEnum::Adjective) {
            exist = true;
            break;
        }
    }
    if(!exist) { return tokens; }

    std::vector<KoreanToken> ret;
    for(auto it = tokens.begin(); it != tokens.end(); ++it){
        if(!ret.empty() && Endings.find(it->pos) != Endings.end()) {
            if(Predicates.find(ret.front().pos) != Predicates.end()) {
                KoreanToken prevToken = ret.front();
                ret = { KoreanToken{prevToken.text + it->text, prevToken.pos, prevToken.offset, prevToken.length + it->length, prevToken.stem, prevToken.unknown}, ret.back() };
            } else {
                ret = std::vector<KoreanToken>(1, *it) * ret;
            }
        } else if(Predicates.find(it->pos) != Predicates.end()) {
            ret = { KoreanToken{it->text, it->pos, it->offset, it->length, mKoreanDictionaryProvider.getPredicateStems()->find(it->pos)->second.find(it->text)->second, it->unknown} };//prevToken.stem, prevToken.unknown}, ret.back() };
        } else {
            ret = std::vector<KoreanToken>(1, *it) * ret;
        }
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}