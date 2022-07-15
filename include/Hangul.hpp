#pragma once
#include <vector>
#include <algorithm>
#include <map>
#include <set>

#define vecIndex(vec,c) (std::find(vec.begin(),vec.end(),c)-vec.begin())

typedef wchar_t Char;

namespace OpenKorean {
struct HangulChar {
    Char onset;
    Char vowel;
    Char coda;
    HangulChar(Char _onset, Char _vowel, Char _coda) : onset(_onset), vowel(_vowel), coda(_coda) {} 
    bool compare(const HangulChar& rhs) {
        return !((rhs.onset != NULL)&&(rhs.onset != this->onset));
    }
};

struct DoubleCoda {
    Char first;
    Char second;
    DoubleCoda(Char firstChar, Char secondChar) : first(firstChar), second(secondChar) {}
};

static const Char HANGUL_BASE = 0xAC00;
static const Char ONSET_BASE = 21*28;
static const Char VOWEL_BASE = 28;

class Hangul {
private:
    static const std::vector<Char> ONSET_LIST;
    static const std::vector<Char> VOWEL_LIST;
    static const std::vector<Char> CODA_LIST;
    static const std::map<Char,DoubleCoda> DOUBLE_CODAS;
public:
    static HangulChar decomposeHangul(Char c) {
        if(std::find(ONSET_LIST.begin(),ONSET_LIST.end(),c) != ONSET_LIST.end() ||
        std::find(VOWEL_LIST.begin(),VOWEL_LIST.end(),c) != VOWEL_LIST.end() ||
        std::find(CODA_LIST.begin(),CODA_LIST.end(),c) != CODA_LIST.end()) {
            return {0,0,0};
        }
        Char u = c - HANGUL_BASE;
        return {ONSET_LIST[u / ONSET_BASE], VOWEL_LIST[(u % ONSET_BASE) / VOWEL_BASE], CODA_LIST[u % VOWEL_BASE]};
    }
    static bool hasCoda(Char c) {
        return ((c - HANGUL_BASE) % VOWEL_BASE > 0) ? true : false;
    }
    static Char composeHangul(Char onset, Char vowel, Char coda = L' ') {
        if(onset == L' ' || vowel == L' ') {
            return 0;
        }
        return (HANGUL_BASE + vecIndex(ONSET_LIST,onset) * ONSET_BASE + vecIndex(VOWEL_LIST,vowel) * VOWEL_BASE + vecIndex(CODA_LIST,coda));
    }
    static Char composeHangul(HangulChar hc) {
        return composeHangul(hc.onset, hc.vowel, hc.coda);
    }
};
}