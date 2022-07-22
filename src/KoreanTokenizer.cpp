#include "KoreanTokenizer.hpp"

using namespace OpenKorean;

const std::map<std::wstring, KoreanPos::KoreanPosEnum> SequenceDefinition = {
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