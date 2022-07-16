#include "KoreanConjugation.hpp"
#include <iostream>

template<typename T>
std::vector<T> operator*(const std::vector<T>& lhs, const std::vector<T>& rhs) {
    std::vector<T> temp;
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


void KoreanConjugation::expanding(ExpandedWord& expanded, bool isAdjective) {
    HangulChar lastChar = expanded.lastCharDecomposed;

    // Cases without codas
    // 하다, special case
    if(lastChar.compare(HangulChar(L'ㅎ', L'ㅏ', L' '))) {
        std::vector<std::wstring> endings;
        if(isAdjective) {
            endings = { L"합", L"해", L"히", L"하" };
        } else {
            endings = { L"합", L"해" };
        }
        const std::vector<std::wstring> common_map = map(CODAS_COMMON,
            [](Char c) { if(c == L'ㅆ') {
                return toString(Hangul::composeHangul(L'ㅎ', L'ㅐ', c));
            } else {
                return toString(Hangul::composeHangul(L'ㅎ', L'ㅏ', c));
            }
        });
        
        expanded.expandedLast = addPreEomi(expanded.lastChar, PRE_EOMI_COMMON * PRE_EOMI_2 * PRE_EOMI_6 * PRE_EOMI_RESPECT) * common_map * addPreEomi(L'하', PRE_EOMI_VOWEL * PRE_EOMI_1_5 * PRE_EOMI_6) * addPreEomi(L'해',PRE_EOMI_1_1) * endings;
        return;
    }

    // 쏘다
    if(lastChar.compare(HangulChar(NullChar, L'ㅗ', L' '))) {
        Char o = lastChar.onset;
        const std::vector<std::wstring> no_past = map(CODAS_NO_PAST,
            [&](Char c) {
                return toString(Hangul::composeHangul(o, L'ㅗ', c));
        });

        expanded.expandedLast = addPreEomi(expanded.lastChar, PRE_EOMI_VOWEL * PRE_EOMI_1_2 * PRE_EOMI_2 * PRE_EOMI_6) * no_past * toStringVector(Hangul::composeHangul(o, L'ㅘ', L' ')) * toStringVector(Hangul::composeHangul(o, L'ㅘ', L'ㅆ')) * toStringVector(expanded.lastChar);
        return;
    }

    // 맞추다, 겨누다, 재우다
    if(lastChar.compare(HangulChar(NullChar, L'ㅜ', L' '))) {
        Char o = lastChar.onset;
        const std::vector<std::wstring> no_past = map(CODAS_NO_PAST,
            [&](Char c) {
                return toString(Hangul::composeHangul(o, L'ㅜ', c));
        });

        expanded.expandedLast = addPreEomi(expanded.lastChar, PRE_EOMI_VOWEL * PRE_EOMI_1_2 * PRE_EOMI_2 * PRE_EOMI_6) * no_past * toStringVector(Hangul::composeHangul(o, L'ㅝ')) * toStringVector(Hangul::composeHangul(o, L'ㅝ', L'ㅆ')) * toStringVector(expanded.lastChar);
        return;
    }

    // 치르다, 구르다, 굴르다, 뜨다, 모으다, 고르다, 골르다
    if(lastChar.compare(HangulChar(NullChar, L'ㅡ', L' '))) {
        Char o = lastChar.onset;
        const std::vector<std::wstring> no_past = map(CODAS_NO_PAST,
            [&](Char c) {
                return toString(Hangul::composeHangul(o, L'ㅡ', c));
        });

        expanded.expandedLast = addPreEomi(expanded.lastChar, PRE_EOMI_2 * PRE_EOMI_6) * no_past
        * toStringVector(Hangul::composeHangul(o, L'ㅝ'))
        * toStringVector(Hangul::composeHangul(o, L'ㅓ'))
        * toStringVector(Hangul::composeHangul(o, L'ㅏ'))
        * toStringVector(Hangul::composeHangul(o, L'ㅝ', L'ㅆ'))
        * toStringVector(Hangul::composeHangul(o, L'ㅓ', L'ㅆ'))
        * toStringVector(Hangul::composeHangul(o, L'ㅏ', L'ㅆ'))
        * toStringVector(expanded.lastChar);
        return;
    }

    // 사귀다
    if(lastChar.compare(HangulChar(L'ㄱ', L'ㅟ', L' '))) {
        const std::vector<std::wstring> no_past = map(CODAS_NO_PAST,
            [](Char c) {
                return toString(Hangul::composeHangul(L'ㄱ', L'ㅟ', c));
        });

        expanded.expandedLast = addPreEomi(expanded.lastChar, PRE_EOMI_2 * PRE_EOMI_6) * no_past
        * toStringVector(Hangul::composeHangul(L'ㄱ', L'ㅕ'))
        * toStringVector(Hangul::composeHangul(L'ㄱ', L'ㅕ', L'ㅆ'))
        * toStringVector(expanded.lastChar);
        return;
    }

    // 쥐다
    if(lastChar.compare(HangulChar(NullChar, L'ㅟ', L' '))) {
        Char o = lastChar.onset;
        const std::vector<std::wstring> no_past = map(CODAS_NO_PAST,
            [&](Char c) {
                return toString(Hangul::composeHangul(o, L'ㅟ', c));
        });

        expanded.expandedLast = no_past * addPreEomi(expanded.lastChar, PRE_EOMI_2 * PRE_EOMI_6) * toStringVector(expanded.lastChar);
        return;
    }

    // 마시다, 엎드리다, 치다, 이다, 아니다
    if(lastChar.compare(HangulChar(NullChar, L'ㅣ', L' '))) {
        Char o = lastChar.onset;
        const std::vector<std::wstring> no_past = map(CODAS_NO_PAST,
            [&](Char c) {
                return toString(Hangul::composeHangul(o, L'ㅣ', c));
        });

        expanded.expandedLast = no_past * addPreEomi(expanded.lastChar, PRE_EOMI_1_2 * PRE_EOMI_2 * PRE_EOMI_6)
        * toStringVector(toString(Hangul::composeHangul(o, L'ㅣ', L'ㅂ')) + L"니")
        * toStringVector(Hangul::composeHangul(o, L'ㅕ'))
        * toStringVector(Hangul::composeHangul(o, L'ㅕ', L'ㅆ'))
        * toStringVector(Hangul::composeHangul(o, L'ㅕ'))
        * toStringVector(expanded.lastChar);
        return;
    }

    // 꿰다, 꾀다
    if(lastChar.compare(HangulChar(NullChar, NullChar, L' '))) {
        Char o = lastChar.onset;
        Char v = lastChar.vowel;
        if(v == L'ㅞ' || v == L'ㅚ' || v == L'ㅙ') {
            const std::vector<std::wstring> common_map = map(CODAS_COMMON,
                [&](Char c) { 
                    return toString(Hangul::composeHangul(o, v, c));
            });
        
            expanded.expandedLast = addPreEomi(expanded.lastChar, PRE_EOMI_2 * PRE_EOMI_6) * common_map * toStringVector(expanded.lastChar);
            return;
        }
    }

    // All other vowel endings: 둘러서다, 켜다, 세다, 캐다, 차다
    if(lastChar.compare(HangulChar(NullChar, NullChar, L' '))) {
        Char o = lastChar.onset;
        Char v = lastChar.vowel;
        const std::vector<std::wstring> common_map = map(CODAS_COMMON,
            [&](Char c) { 
                return toString(Hangul::composeHangul(o, v, c));
        });
        
        expanded.expandedLast = common_map * addPreEomi(expanded.lastChar, PRE_EOMI_VOWEL * PRE_EOMI_1_1 * PRE_EOMI_2 * PRE_EOMI_6) * toStringVector(expanded.lastChar);
        return;
    }

    // Cases with codas
    // 만들다, 알다, 풀다
    if(lastChar.compare(HangulChar(NullChar, NullChar, L'ㄹ'))) {
        Char o = lastChar.onset;
        Char v = lastChar.vowel;
        if((o == L'ㅁ' && v == L'ㅓ') || v == L'ㅡ' || v == L'ㅏ' || v == L'ㅜ') {
            expanded.expandedLast = addPreEomi(expanded.lastChar, PRE_EOMI_1_2 * PRE_EOMI_3)
            * addPreEomi(Hangul::composeHangul(o, v, L' '), PRE_EOMI_2 * PRE_EOMI_6 * PRE_EOMI_RESPECT)
            * toStringVector(Hangul::composeHangul(o, v, L'ㄻ'))
            * toStringVector(Hangul::composeHangul(o, v, L'ㄴ'))
            * toStringVector(expanded.lastChar);
            return;
        }
    }
}
