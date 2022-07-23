#pragma once
#include "KoreanPos.hpp"

namespace OpenKorean {
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
        return L"";
    }

    KoreanToken copyWithNewPos(KoreanPos::KoreanPosEnum pos) {
        return {this->text, pos, this->offset, this->length, std::wstring(), this->unknown};
    }
};
}