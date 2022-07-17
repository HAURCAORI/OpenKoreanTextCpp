#pragma once
#include "Hangul.hpp"

namespace OpenKorean {
class KoreanSubstantive {
private:
    static const std::set<Char> JOSA_HEAD_FOR_CODA;
    static const std::set<Char> JOSA_HEAD_FOR_NO_CODA;

public:
    static bool isJosaAttachable(Char prevChar, Char headChar);
    
};
}