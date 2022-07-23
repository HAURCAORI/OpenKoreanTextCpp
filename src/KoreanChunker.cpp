#include "KoreanChunker.hpp"

using namespace OpenKorean;


const std::map<KoreanPos::KoreanPosEnum, std::wregex> KoreanChunker::POS_PATTERNS = {
    { KoreanPos::KoreanPosEnum::Korean, std::wregex(LR"(([가-힣]+))") },
    { KoreanPos::KoreanPosEnum::Alpha, std::wregex(LR"((\p{Alpha}+))") },
    { KoreanPos::KoreanPosEnum::Number, std::wregex(LR"(    )") },
    { KoreanPos::KoreanPosEnum::KoreanParticle, std::wregex(LR"(([ㄱ-ㅣ]+))") },
    { KoreanPos::KoreanPosEnum::Punctuation, std::wregex(LR"(([\p{Punct}·…’]+))") },
    { KoreanPos::KoreanPosEnum::URL, std::wregex(LR"(    )") },
    { KoreanPos::KoreanPosEnum::Email, std::wregex(LR"(([\p{Alnum}\.\-_]+@[\p{Alnum}\.]+))") },
    { KoreanPos::KoreanPosEnum::Hashtag, std::wregex(LR"(    )") },
    { KoreanPos::KoreanPosEnum::ScreenName, std::wregex(LR"(    )") },
    { KoreanPos::KoreanPosEnum::CashTag, std::wregex(LR"(    )") },
    { KoreanPos::KoreanPosEnum::Space, std::wregex(LR"(\s+)") },
/*

Korean -> """([가-힣]+)""".r.pattern,
    Alpha -> """(\p{Alpha}+)""".r.pattern,
    Number -> ("""(\$?\p{Digit}+"""
      + """(,\p{Digit}{3})*([/~:\.-]\p{Digit}+)?"""
      + """(천|만|억|조)*(%|원|달러|위안|옌|엔|유로|등|년|월|일|회|시간|시|분|초)?)""").r.pattern,
    KoreanParticle -> """([ㄱ-ㅣ]+)""".r.pattern,
    Punctuation -> """([\p{Punct}·…’]+)""".r.pattern,
    URL -> Regex.VALID_URL,
    Email -> """([\p{Alnum}\.\-_]+@[\p{Alnum}\.]+)""".r.pattern,
    Hashtag -> Regex.VALID_HASHTAG,
    ScreenName -> Regex.VALID_MENTION_OR_LIST,
    CashTag -> Regex.VALID_CASHTAG,
    Space -> """\s+""".r.pattern

    */
};