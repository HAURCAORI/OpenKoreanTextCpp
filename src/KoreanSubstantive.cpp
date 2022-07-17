#include "KoreanSubstantive.hpp"

using namespace OpenKorean;


const std::set<Char> KoreanSubstantive::JOSA_HEAD_FOR_CODA = {L'은', L'이', L'을', L'과', L'아'};
const std::set<Char> KoreanSubstantive::JOSA_HEAD_FOR_NO_CODA = {L'는', L'가', L'를', L'와', L'야', L'여', L'라'};

bool KoreanSubstantive::isJosaAttachable(Char prevChar, Char headChar) {
    return (Hangul::hasCoda(prevChar) && !findSet(JOSA_HEAD_FOR_NO_CODA,headChar)) || (!Hangul::hasCoda(prevChar) && !findSet(JOSA_HEAD_FOR_CODA,headChar));
}
