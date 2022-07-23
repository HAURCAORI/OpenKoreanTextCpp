#include "KoreanPos.hpp"
#define cmap(arg) {KoreanPosEnum::arg, #arg}

using namespace OpenKorean;

template<typename T>
std::vector<T> operator*(const std::vector<T>& lhs, const std::vector<T>& rhs) {
    std::vector<T> temp;
    temp.insert(temp.begin(), lhs.begin(), lhs.end());
    temp.insert(temp.begin(), rhs.begin(), rhs.end());
    return temp;
}

const std::set<KoreanPos::KoreanPosEnum> KoreanPos::OtherPoses = {
    KoreanPosEnum::Korean, KoreanPosEnum::Foreign, KoreanPosEnum::Number, KoreanPosEnum::KoreanParticle, KoreanPosEnum::Alpha,
    KoreanPosEnum::Punctuation, KoreanPosEnum::Hashtag, KoreanPosEnum::ScreenName,
    KoreanPosEnum::Email, KoreanPosEnum::URL, KoreanPosEnum::CashTag
};

const std::map<KoreanPos::KoreanPosEnum, std::string> KoreanPos::TagString = {
    cmap(Noun), cmap(Verb), cmap(Adjective), cmap(Adverb), cmap(Determiner), cmap(Exclamation), cmap(Josa),
    cmap(Eomi), cmap(PreEomi), cmap(Conjunction), cmap(Modifier), cmap(VerbPrefix), cmap(Suffix), cmap(Unknown),

    cmap(Korean), cmap(Foreign), cmap(Number), cmap(KoreanParticle), cmap(Alpha),
    cmap(Punctuation), cmap(Hashtag), cmap(ScreenName), cmap(Email), cmap(URL), cmap(CashTag),

    cmap(Space), cmap(Others), cmap(ProperNoun),
    cmap(SpamNouns), cmap(FamilyName), cmap(GivenName), cmap(FullName)
};

const std::map<wchar_t, KoreanPos::KoreanPosEnum> KoreanPos::shortCut = {
    {L'N',KoreanPosEnum::Noun},
    {L'V',KoreanPosEnum::Verb},
    {L'J',KoreanPosEnum::Adjective},
    {L'A',KoreanPosEnum::Adverb},
    {L'D',KoreanPosEnum::Determiner},
    {L'E',KoreanPosEnum::Exclamation},
    {L'C',KoreanPosEnum::Conjunction},

    {L'j',KoreanPosEnum::Josa},
    {L'e',KoreanPosEnum::Eomi},
    {L'r',KoreanPosEnum::PreEomi},
    {L'm',KoreanPosEnum::Modifier},
    {L'v',KoreanPosEnum::VerbPrefix},
    {L's',KoreanPosEnum::Suffix},

    {L'a',KoreanPosEnum::Alpha},
    {L'n',KoreanPosEnum::Number},

    {L'o',KoreanPosEnum::Others}
};

const std::set<KoreanPos::KoreanPosEnum> KoreanPos::Predicates = {KoreanPosEnum::Verb, KoreanPosEnum::Adjective};

std::vector<KoreanPosTrie> KoreanPos::buildTrie(const std::wstring& s, KoreanPosEnum ending_pos) {
    if(s.length() < 2) { return std::vector<KoreanPosTrie>(); }

    KoreanPosEnum pos = shortCut.find(s[0])->second;
    wchar_t rule = s[1];
    std::wstring rest = s.substr(2);
    
    KoreanPosEnum end = (isFinal(rest)) ? ending_pos : KoreanPosEnum::Null;
    

    if(rule == L'+')
        return std::vector<KoreanPosTrie>(1, KoreanPosTrie{pos, KoreanPosTrie::selfNodeVec() * buildTrie(rest, ending_pos), end});
    if(rule == L'*')
        return std::vector<KoreanPosTrie>(1, KoreanPosTrie{pos, KoreanPosTrie::selfNodeVec() * buildTrie(rest, ending_pos), end}) * buildTrie(rest ,ending_pos);
    if(rule == L'1')
        return std::vector<KoreanPosTrie>(1, KoreanPosTrie{pos, buildTrie(rest, ending_pos), end});
    if(rule == L'0')
        return std::vector<KoreanPosTrie>(1, KoreanPosTrie{pos, buildTrie(rest, ending_pos), end}) * buildTrie(rest ,ending_pos);
    
    return std::vector<KoreanPosTrie>();
};

std::vector<KoreanPosTrie> KoreanPos::getTrie(std::map<std::wstring, KoreanPos::KoreanPosEnum> sequences) {
    std::vector<KoreanPosTrie> ret;
    for(auto it = sequences.begin(); it != sequences.end(); ++it) {
        ret = buildTrie(it->first,it->second) * ret;
    }
    return ret;
}
