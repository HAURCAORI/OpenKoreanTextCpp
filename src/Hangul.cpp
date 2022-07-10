#include "Hangul.hpp"

using namespace OpenKorean;

const std::vector<Char> Hangul::ONSET_LIST = {
    L'ㄱ', L'ㄲ', L'ㄴ', L'ㄷ', L'ㄸ', L'ㄹ', L'ㅁ', L'ㅂ', L'ㅃ',
    L'ㅅ', L'ㅆ', L'ㅇ', L'ㅈ', L'ㅉ', L'ㅊ', L'ㅋ', L'ㅌ', L'ㅍ', L'ㅎ'
};
const std::vector<Char> Hangul::VOWEL_LIST = {
    L'ㅏ', L'ㅐ', L'ㅑ', L'ㅒ', L'ㅓ', L'ㅔ',
    L'ㅕ', L'ㅖ', L'ㅗ', L'ㅘ', L'ㅙ', L'ㅚ',
    L'ㅛ', L'ㅜ', L'ㅝ', L'ㅞ', L'ㅟ', L'ㅠ',
    L'ㅡ', L'ㅢ', L'ㅣ'
};
const std::vector<Char> Hangul::CODA_LIST = {
    L' ', L'ㄱ', L'ㄲ', L'ㄳ', L'ㄴ', L'ㄵ', L'ㄶ', L'ㄷ',
    L'ㄹ', L'ㄺ', L'ㄻ', L'ㄼ', L'ㄽ', L'ㄾ', L'ㄿ', L'ㅀ',
    L'ㅁ', L'ㅂ', L'ㅄ', L'ㅅ', L'ㅆ', L'ㅇ', L'ㅈ', L'ㅊ',
    L'ㅋ', L'ㅌ', L'ㅍ', L'ㅎ'
};

const std::map<Char,DoubleCoda> Hangul::DOUBLE_CODAS = {
    {L'ㄳ' , DoubleCoda(L'ㄱ', L'ㅅ')},
    {L'ㄵ' , DoubleCoda(L'ㄴ', L'ㅈ')},
    {L'ㄶ' , DoubleCoda(L'ㄴ', L'ㅎ')},
    {L'ㄺ' , DoubleCoda(L'ㄹ', L'ㄱ')},
    {L'ㄻ' , DoubleCoda(L'ㄹ', L'ㅁ')}, 
    {L'ㄼ' , DoubleCoda(L'ㄹ', L'ㅂ')},
    {L'ㄽ' , DoubleCoda(L'ㄹ', L'ㅅ')},
    {L'ㄾ' , DoubleCoda(L'ㄹ', L'ㅌ')},
    {L'ㄿ' , DoubleCoda(L'ㄹ', L'ㅍ')},
    {L'ㅀ' , DoubleCoda(L'ㄹ', L'ㅎ')},
    {L'ㅄ' , DoubleCoda(L'ㅂ', L'ㅅ')}
};
