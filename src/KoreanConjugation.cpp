#include "KoreanConjugation.hpp"

std::vector<Char> operator*(const std::vector<Char>& lhs, const std::vector<Char>& rhs) {
    std::vector<Char> temp;
    temp.insert(temp.begin(), lhs.begin(), lhs.end());
    temp.insert(temp.begin(), rhs.begin(), rhs.end());
    return temp;
}

using namespace OpenKorean;

const std::vector<Char> KoreanConjugation::CODAS_COMMON = {L'ㅂ', L'ㅆ', L'ㄹ', L'ㄴ', L'ㅁ'};
const std::vector<Char> KoreanConjugation::CODAS_FOR_CONTRACTION = {L'ㅆ', L'ㄹ', L'ㅁ'};
const std::vector<Char> KoreanConjugation::CODAS_NO_PAST = {L'ㅂ', L'ㄹ', L'ㄴ', L'ㅁ'};

const std::vector<Char> KoreanConjugation::CODAS_SLANG_CONSONANT = {L'ㅋ', L'ㅎ'};
const std::vector<Char> KoreanConjugation::CODAS_SLANG_VOWEL = {L'ㅜ', L'ㅠ'};

const std::vector<Char> KoreanConjugation::PRE_EOMI_COMMON = {
    L'게', L'겠', L'고', L'구', L'기',
    L'긴', L'길', L'네', L'다', L'더',
    L'던', L'도', L'든', L'면', L'자',
    L'잖', L'재', L'져', L'죠', L'지', L'진', L'질'
};
const std::vector<Char> KoreanConjugation::PRE_EOMI_1_1 = { L'야', L'서', L'써', L'도', L'준' };
const std::vector<Char> KoreanConjugation::PRE_EOMI_1_2 = { L'어', L'었' };
const std::vector<Char> KoreanConjugation::PRE_EOMI_1_3 = { L'아', L'았' };
const std::vector<Char> KoreanConjugation::PRE_EOMI_1_4 = { L'워', L'웠' };
const std::vector<Char> KoreanConjugation::PRE_EOMI_1_5 = { L'여', L'였' };

const std::vector<Char> KoreanConjugation::PRE_EOMI_2 = { L'노', L'느', L'니', L'냐' };
const std::vector<Char> KoreanConjugation::PRE_EOMI_3 = { L'러', L'려', L'며' };
const std::vector<Char> KoreanConjugation::PRE_EOMI_4 = { L'으' };
const std::vector<Char> KoreanConjugation::PRE_EOMI_5 = { L'은' };
const std::vector<Char> KoreanConjugation::PRE_EOMI_6 = { L'는' };
const std::vector<Char> KoreanConjugation::PRE_EOMI_7 = { L'운' };
const std::vector<Char> KoreanConjugation::PRE_EOMI_RESPECT = { L'세', L'시', L'실', L'신', L'셔', L'습', L'셨', L'십' };

const std::vector<Char> KoreanConjugation::PRE_EOMI_VOWEL = KoreanConjugation::PRE_EOMI_COMMON * KoreanConjugation::PRE_EOMI_2 * KoreanConjugation::PRE_EOMI_3 * KoreanConjugation::PRE_EOMI_RESPECT;