#include "KoreanChunker.hpp"

using namespace OpenKorean;


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