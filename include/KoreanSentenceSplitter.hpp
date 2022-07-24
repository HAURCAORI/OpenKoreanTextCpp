#pragma once
#include <string>
#include <regex>

namespace OpenKorean {
struct Sentence {
    std::wstring text;
    int start;
    int end;
};

class KoreanSentenceSplitter {
public:
static std::wregex re() {
    return std::wregex(LR"((?x)[^.!?…\s][^.!?…]*(?:[.!?…](?!['\"]?\s|$)[^.!?…]*)*[.!?…]?['\"]?(?=\s|$))");
}
/*
    """(?x)[^.!?…\s]   # First char is non-punct, non-ws
      [^.!?…]*         # Greedily consume up to punctuation.
      (?:              # Group for unrolling the loop.
        [.!?…]         # (special) inner punctuation ok if
        (?!['\"]?\s|$) # not followed by ws or EOS.
        [^.!?…]*       # Greedily consume up to punctuation.
      )*               # Zero or more (special normal*)
      [.!?…]?          # Optional ending punctuation.
      ['\"]?           # Optional closing quote.
      (?=\s|$)""".r
*/

static std::vector<Sentence> split(const std::wstring& s) {
    std::wregex reg = re();
    auto start = std::wsregex_iterator(s.begin(), s.end(), reg);
    auto end = std::wsregex_iterator();
    if(start == end) { return std::vector<Sentence>(1, Sentence{s,0,(signed) s.length()}); } // 매칭 결과가 없을 시 
    
    std::vector<Sentence> ret;
    while(start != end) {
        ret.push_back(Sentence{(*start)[0], start->position(0), start->position(0) + (*start)[0].length()}); // start to end
        ++start;
    }
    return ret;
}

};
}