#include "KoreanSubstantive.hpp"

using namespace OpenKorean;

inline std::wstring string_init(const std::wstring& str) {
    return str.substr(0, (str.length() > 1) ? str.length()-1 : 0);
}

const std::set<Char> KoreanSubstantive::JOSA_HEAD_FOR_CODA = {L'은', L'이', L'을', L'과', L'아'};
const std::set<Char> KoreanSubstantive::JOSA_HEAD_FOR_NO_CODA = {L'는', L'가', L'를', L'와', L'야', L'여', L'라'};
const std::set<Char> KoreanSubstantive::NUMBER_CHARS = {
    L'일', L'이', L'삼', L'사', L'오', L'육', L'칠', L'팔', L'구',
    L'천', L'백', L'십', L'해', L'경', L'조', L'억', L'만' 
};
const std::set<Char> KoreanSubstantive::NUMBER_LAST_CHARS = {
    L'일', L'이', L'삼', L'사', L'오', L'육', L'칠', L'팔', L'구',
    L'천', L'백', L'십', L'해', L'경', L'조', L'억', L'만',
    L'원', L'배', L'분', L'초'
};

bool KoreanSubstantive::isJosaAttachable(Char prevChar, Char headChar) {
    return (Hangul::hasCoda(prevChar) && !findSet(JOSA_HEAD_FOR_NO_CODA,headChar)) || (!Hangul::hasCoda(prevChar) && !findSet(JOSA_HEAD_FOR_CODA,headChar));
}

bool KoreanSubstantive::isKoreanNumber(const std::wstring& chunk) {
    bool output = true;
    for(int i = 0; i < (signed) chunk.length(); ++i) {
        if(i < (signed) chunk.length() - 1) {
            output = output && (NUMBER_CHARS.find(chunk[i]) != NUMBER_CHARS.end());
        } else {
            output = output && (NUMBER_LAST_CHARS.find(chunk[i]) != NUMBER_LAST_CHARS.end());
        }
    }
    return output;
}

bool KoreanSubstantive::isName(const std::wstring& chunk) {
    if(mKoreanDictionaryProvider.contain(KoreanPos::KoreanPosEnum::FullName, chunk) || mKoreanDictionaryProvider.contain(KoreanPos::KoreanPosEnum::GivenName, chunk)) {
        return true;
    }
    if(chunk.length() == 3) {
        return mKoreanDictionaryProvider.contain(KoreanPos::KoreanPosEnum::FamilyName, chunk.substr(0,1)) && 
        mKoreanDictionaryProvider.contain(KoreanPos::KoreanPosEnum::GivenName, chunk.substr(2));
    } else if(chunk.length() == 4) {
        return mKoreanDictionaryProvider.contain(KoreanPos::KoreanPosEnum::FamilyName, chunk.substr(0,2)) && 
        mKoreanDictionaryProvider.contain(KoreanPos::KoreanPosEnum::GivenName, chunk.substr(2));
    } else {
        return false;
    }
}

bool KoreanSubstantive::isKoreanNameVariation(const std::wstring& chunk) {
    if(isName(chunk)) { return true; }
    if(chunk.length() < 3 || chunk.length() > 5) { return false; }

    std::vector<HangulChar> decomposed;
    for(auto it = chunk.begin(); it != chunk.end(); ++it) {
        decomposed.push_back(Hangul::decomposeHangul(*it));
    }
    HangulChar lastChar = decomposed.back();
    if(Hangul::CODA_SET.find(lastChar.onset) == Hangul::CODA_SET.end()) { return false; }
    if(lastChar.onset == L'ㅇ' || lastChar.vowel != L'ㅣ' || lastChar.coda != L' ') { return false; }
    if(decomposed[decomposed.size()-2].coda != L' ') { return false; }

    std::wstring recovered = L"";
    int i = 0;
    for(auto it = decomposed.begin(); it != decomposed.end(); ++it) {
        if(i == (signed) chunk.length() - 1) { recovered += L"이"; }
        else if(i == (signed) chunk.length() - 2) {
            recovered += std::wstring(1, Hangul::composeHangul(HangulChar(it->onset, it->vowel, lastChar.onset)));
        }
        else {
            recovered += std::wstring(1, Hangul::composeHangul(*it));
        }
    }
    
    return isName(recovered) || isName(string_init(recovered));
}

std::vector<KoreanToken> KoreanSubstantive::collapseNouns(const std::vector<KoreanToken>& posNodes) {
    std::vector<KoreanToken> pl = std::vector<KoreanToken>();
    bool collapsing = false;
    for(auto p = posNodes.begin(); p != posNodes.end(); ++p) {
        if(p->pos == KoreanPos::KoreanPosEnum::Noun && p->text.length() == 1 && collapsing) {
            std::wstring text = pl.front().text + p->text;
            int offset = pl.front().offset;
            pl.erase(pl.begin());
            pl.insert(pl.begin(), KoreanToken{text, KoreanPos::KoreanPosEnum::Noun, offset, (signed) text.length(), std::wstring(), true});
            collapsing = true;
        } else if(p->pos == KoreanPos::KoreanPosEnum::Noun && p->text.length() == 1 && !collapsing) {
            pl.insert(pl.begin(), *p);
            collapsing = true;
        } else {
            pl.insert(pl.begin(), *p);
            collapsing = false;
        }
    }
    std::reverse(pl.begin(), pl.end());
    return pl;
}