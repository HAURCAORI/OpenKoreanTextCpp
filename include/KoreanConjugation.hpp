#pragma once
#include "Hangul.hpp"
#include <unordered_set>
#include <functional>


namespace OpenKorean {

typedef std::unordered_set<std::wstring> Dictionary;

struct ExpandedWord {
    std::wstring init;
    Char lastChar;
    std::wstring lastCharString;
    HangulChar lastCharDecomposed;
    ExpandedWord(const std::wstring& str) : init(getInit(str)), lastChar(str.back()), lastCharString(1,lastChar), lastCharDecomposed(Hangul::decomposeHangul(lastChar)) {}
};

class KoreanConjugation {
private:
    static const std::vector<Char> CODAS_COMMON;
    static const std::vector<Char> CODAS_FOR_CONTRACTION;
    static const std::vector<Char> CODAS_NO_PAST;
    static const std::vector<Char> CODAS_SLANG_CONSONANT;
    static const std::vector<Char> CODAS_SLANG_VOWEL;
    static const std::vector<Char> PRE_EOMI_COMMON;
    static const std::vector<Char> PRE_EOMI_1_1;
    static const std::vector<Char> PRE_EOMI_1_2;
    static const std::vector<Char> PRE_EOMI_1_3;
    static const std::vector<Char> PRE_EOMI_1_4;
    static const std::vector<Char> PRE_EOMI_1_5;

    static const std::vector<Char> PRE_EOMI_2;
    static const std::vector<Char> PRE_EOMI_3;
    static const std::vector<Char> PRE_EOMI_4;
    static const std::vector<Char> PRE_EOMI_5;
    static const std::vector<Char> PRE_EOMI_6;
    static const std::vector<Char> PRE_EOMI_7;

    static const std::vector<Char> PRE_EOMI_RESPECT;

    static const std::vector<Char> PRE_EOMI_VOWEL;
    static std::vector<std::wstring> expanding(const ExpandedWord& expanded, bool isAdjective);
    static std::vector<std::wstring> expanding_irregular(const ExpandedWord& expanded);

    static std::vector<std::wstring> map(const std::vector<Char>& chars, const std::function<std::wstring(Char)>& lambda) {
        std::vector<std::wstring> ret;
        ret.reserve(chars.size());
        for(auto it = chars.begin(); it != chars.end(); ++it) {
            ret.push_back(lambda(*it));
        }
        return ret;
    }

public:
    static std::vector<std::wstring> addPreEomi(Char lastChar, std::vector<Char> charsToAdd) {
        std::vector<std::wstring> ret;
        for(auto it = charsToAdd.begin(); it != charsToAdd.end(); ++it) {
            std::wstring ws(1, lastChar);
            ws.append(1,*it);
            ret.push_back(ws);
        }
        return ret;
    }
    
    /*
    protected[processor] def conjugatePredicatesToCharArraySet(words: Set[String], isAdjective: Boolean = false): CharArraySet = {
    val expanded: Set[String] = conjugatePredicated(words, isAdjective)

    val newSet = newCharArraySet
    newSet.addAll(expanded.asJava)
    newSet
    }*/


    static Dictionary conjugatePredicated(const std::wstring& words, bool isAdjective = false);
    static Dictionary conjugatePredicated(const std::vector<std::wstring>& vec_words, bool isAdjective = false);
    static std::map<std::wstring, std::wstring> getConjugationMap(const std::vector<std::wstring>& words, bool isAdjective);
};
}