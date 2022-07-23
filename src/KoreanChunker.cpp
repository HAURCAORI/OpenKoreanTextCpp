#include "KoreanChunker.hpp"
#include <algorithm>
#include <iostream>
using namespace OpenKorean;

inline int Start(std::wsregex_iterator it) {
  return it->position(0);
}

inline int End(std::wsregex_iterator it) {
  return it->position(0) + (*it)[0].length();
}

inline std::wstring substrPos(const std::wstring& str, size_t start, size_t end) {
  if(end < start) { return str; }
  if(start > str.length()) { return L""; }
  return str.substr(start, end - start);
}

const std::map<KoreanPos::KoreanPosEnum, std::wregex> KoreanChunker::POS_PATTERNS = {
    { KoreanPos::KoreanPosEnum::Korean, std::wregex(LR"(([가-힣]+))") },
    { KoreanPos::KoreanPosEnum::Alpha, std::wregex(LR"(([a-zA-Z]+))") },
    { KoreanPos::KoreanPosEnum::Number, std::wregex(LR"((\$?[0-9]+(,[0-9]{3})*([/~:\.-][0-9]+)?(천|만|억|조)*(%|원|달러|위안|옌|엔|유로|등|년|월|일|회|시간|시|분|초)?))") },
    { KoreanPos::KoreanPosEnum::KoreanParticle, std::wregex(LR"(([ㄱ-ㅣ]+))") },
    { KoreanPos::KoreanPosEnum::Punctuation, std::wregex(LR"(([^\s\w]|[_])+)") },
    { KoreanPos::KoreanPosEnum::URL, std::wregex(LR"([-a-zA-Z0-9@:%_\+.~#?&//=]{2,256}\.[a-z]{2,4}\b(\/[-a-zA-Z0-9@:%_\+.~#?&//=]*)?)") },
    { KoreanPos::KoreanPosEnum::Email, std::wregex(LR"(([a-zA-Z0-9\.\-_]+@[a-zA-Z0-9\.]+))") },
    { KoreanPos::KoreanPosEnum::Hashtag, std::wregex(LR"(([#＃]+)([a-zA-Z가-힣_]+[a-zA-Z0-9가-힣_]*))") },
    { KoreanPos::KoreanPosEnum::ScreenName, std::wregex(LR"(\B@[a-z0-9_-]+)") },
    { KoreanPos::KoreanPosEnum::CashTag, std::wregex(LR"(\$?(\d+)\.?(\d+)?)") },
    { KoreanPos::KoreanPosEnum::Space, std::wregex(LR"(\s+)") }
};

const std::vector<KoreanPos::KoreanPosEnum> KoreanChunker::CHUNKING_ORDER = { KoreanPos::KoreanPosEnum::URL, KoreanPos::KoreanPosEnum::Email, KoreanPos::KoreanPosEnum::ScreenName,
    KoreanPos::KoreanPosEnum::Hashtag, KoreanPos::KoreanPosEnum::CashTag, KoreanPos::KoreanPosEnum::Number,
    KoreanPos::KoreanPosEnum::Korean, KoreanPos::KoreanPosEnum::KoreanParticle, KoreanPos::KoreanPosEnum::Alpha,
    KoreanPos::KoreanPosEnum::Punctuation
};

//std::vector<ChunkMatch> KoreanChunker::findAllPatterns(const std::wsmatch& match, KoreanPos::KoreanPosEnum pos, const std::vector<ChunkMatch>& matches) {}
std::vector<ChunkMatch> KoreanChunker::splitChunks(const std::wstring& text) {
  if(text[0] == L' ') {
    return std::vector<ChunkMatch>(1, ChunkMatch{0, (signed) text.length() , text, KoreanPos::KoreanPosEnum::Space});
  } else {
    std::vector<ChunkMatch> ret;
    int matchedLen = 0;
    for(auto it = CHUNKING_ORDER.begin(); it != CHUNKING_ORDER.end(); ++it) {
      if(matchedLen < (signed) text.length()) {
        auto start = std::wsregex_iterator(text.begin(), text.end(), POS_PATTERNS.find(*it)->second);
        auto end = std::wsregex_iterator();
        
        while(start != end) {
          ChunkMatch cm = {Start(start), End(start), (*start)[0], *it};
          if(std::all_of(ret.begin(), ret.end(), [&](const ChunkMatch& rcm) { return cm.disjoint(rcm); } )) {
            ret.push_back(cm);
            matchedLen += cm.end - cm.start;
          }
        }
      }
    }
    std::sort(ret.begin(), ret.end(), [](const ChunkMatch& T, const ChunkMatch& U) -> bool { return T.start < U.start; } );
    fillInUnmatched(text, ret, KoreanPos::KoreanPosEnum::Foreign);
  }
}
std::vector<ChunkMatch> KoreanChunker::fillInUnmatched(const std::wstring& text, const std::vector<ChunkMatch>& chunks, KoreanPos::KoreanPosEnum pos) {
  std::vector<ChunkMatch> ret;
  int prevEnd = 0;
  for(auto it = chunks.begin(); it != chunks.end(); ++it) {
    if(it->start == prevEnd) {
      ret.insert(ret.begin(),*it);
      prevEnd = it->end;
    } else if(it->start > prevEnd) {
      ret.insert(ret.begin(), ChunkMatch{prevEnd, it->start, substrPos(text, prevEnd, it->start) , pos});
      ret.insert(ret.begin(),*it);
      prevEnd = it->end;
    } else {
      throw std::ios_base::failure("Non-disjoint chunk matches found.");
    }
  }
  if(prevEnd < (signed) text.length()) {
    ret.insert(ret.begin(), ChunkMatch{prevEnd, (signed) text.length(), substrPos(text, prevEnd, text.length()), pos});
  }
  return ret;
}

//std::vector<std::wstring> getChunks(const std::wstring& input, bool keepSpace = false);
std::vector<std::wstring> KoreanChunker::splitBySpaceKeepingSpace(const std::wstring& s) {
  std::wregex space(LR"(\s+)");
  auto start = std::wsregex_iterator(s.begin(), s.end(), space);
  auto end = std::wsregex_iterator();

  if(start == end) { return {s}; } // 매칭 결과가 없을 시

  std::vector<std::wstring> tokens;
  int index = 0;
  while(start != end) {
    if(index < start->position(0)) {
      tokens.push_back(substrPos(s, index, Start(start)));
    }
    tokens.push_back(substrPos(s, Start(start), End(start)));
    index = End(start);
    ++start;
  }
  if(index < (signed) s.length()) {
    tokens.push_back(s.substr(index));
  }
  return tokens;
}
//std::vector<KoreanToken> getChunksByPos(const std::wstring& input, KoreanPos::KoreanPosEnum pos);

std::vector<KoreanToken> KoreanChunker::chunk(const std::wstring& input) {
  
}