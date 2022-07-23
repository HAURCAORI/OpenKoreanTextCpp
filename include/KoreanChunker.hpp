#pragma once
#include "KoreanPos.hpp"
#include <regex>

namespace OpenKorean {
struct KoreanChunk {
    std::wstring text;
    int offset;
    int length;
};

class KoreanChunker {
private:
    static const std::map<KoreanPos::KoreanPosEnum, std::wregex> POS_PATTERNS;
    
public:

};

};