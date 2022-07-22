#include "KoreanPos.hpp"
#define cmap(arg) {KoreanPosEnum::arg, #arg}

using namespace OpenKorean;

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

const std::map<char, KoreanPos::KoreanPosEnum> KoreanPos::shortCut = {
    {'N',KoreanPosEnum::Noun},
    {'V',KoreanPosEnum::Verb},
    {'J',KoreanPosEnum::Adjective},
    {'A',KoreanPosEnum::Adverb},
    {'D',KoreanPosEnum::Determiner},
    {'E',KoreanPosEnum::Exclamation},
    {'C',KoreanPosEnum::Conjunction},

    {'j',KoreanPosEnum::Josa},
    {'e',KoreanPosEnum::Eomi},
    {'r',KoreanPosEnum::PreEomi},
    {'m',KoreanPosEnum::Modifier},
    {'v',KoreanPosEnum::VerbPrefix},
    {'s',KoreanPosEnum::Suffix},

    {'a',KoreanPosEnum::Alpha},
    {'n',KoreanPosEnum::Number},

    {'o',KoreanPosEnum::Others}
};

const std::set<KoreanPos::KoreanPosEnum> KoreanPos::Predicates = {KoreanPosEnum::Verb, KoreanPosEnum::Adjective};