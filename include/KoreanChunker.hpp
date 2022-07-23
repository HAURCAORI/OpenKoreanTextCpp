#pragma once
#include "KoreanPos.hpp"
#include "KoreanToken.hpp"
#include <regex>

namespace OpenKorean {
struct KoreanChunk {
    std::wstring text;
    int offset;
    int length;
};

struct ChunkMatch {
    int start;
    int end;
    std::wstring text;
    KoreanPos::KoreanPosEnum pos;

    bool disjoint(const ChunkMatch& that) {
        return (that.start < this->start && that.end <= this->start) || (that.start >= this->end && that.end > this->end);
    }
};

class KoreanChunker {
private:
    static const std::map<KoreanPos::KoreanPosEnum, std::wregex> POS_PATTERNS;
    static const std::vector<KoreanPos::KoreanPosEnum> CHUNKING_ORDER;
    
    static std::vector<ChunkMatch> findAllPatterns(const std::wsmatch& match, KoreanPos::KoreanPosEnum pos, const std::vector<ChunkMatch>& matches = std::vector<ChunkMatch>());
    static std::vector<ChunkMatch> splitChunks(const std::wstring& text);
    static std::vector<ChunkMatch> fillInUnmatched(const std::wstring& text, const std::vector<ChunkMatch>& chunks, KoreanPos::KoreanPosEnum pos);
public:
    static std::vector<std::wstring> getChunks(const std::wstring& input, bool keepSpace = false);
    static std::vector<std::wstring> splitBySpaceKeepingSpace(const std::wstring& s);
    static std::vector<KoreanToken> getChunksByPos(const std::wstring& input, KoreanPos::KoreanPosEnum pos);
    static std::vector<KoreanToken> chunk(const std::wstring& input);
};

};