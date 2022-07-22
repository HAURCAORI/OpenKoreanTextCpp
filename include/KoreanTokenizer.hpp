#pragma once
#include <map>
#include "KoreanPos.hpp"

namespace OpenKorean {
class KoreanTokenizer {
private:
    static const int TOP_N_PER_STATE = 5;
    static const int MAX_TRACE_BACK = 8;
    static const std::map<std::wstring, KoreanPos::KoreanPosEnum> SequenceDefinition;

    
public:

};

struct KoreanToken {
    std::wstring text;
    KoreanPos::KoreanPosEnum pos;
    int offset;
    int length;
    std::wstring stem = std::wstring();
    bool unknown = false;

    std::wstring toString() {
        //val unknownStar = if (unknown) "*" else ""
        //val stemString = if (stem.isDefined) "(%s)".format(stem.get) else ""
        //s"$text$unknownStar(${pos.toString}$stemString: $offset, $length)"
    }

    KoreanToken copyWithNewPos(KoreanPos::KoreanPosEnum pos) {
        return {this->text, pos, this->offset, this->length, std::wstring(), this->unknown};
    }
};
}