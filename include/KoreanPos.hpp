#ifndef _KOREAN_POS_HPP_
#define _KOREAN_POS_HPP_

#include <map>
#include <set>
/**
 * Korean Part-of-Speech
 *
 * N Noun: 명사 (Nouns, Pronouns, Company Names, Proper Noun, Person Names, Numerals, Standalone, Dependent)
 * V Verb: 동사 (하, 먹, 자, 차)
 * J Adjective: 형용사 (예쁘다, 크다, 작다)
 * A Adverb: 부사 (잘, 매우, 빨리, 반드시, 과연)
 * D Determiner: 관형사 (새, 헌, 참, 첫, 이, 그, 저)
 * E Exclamation: 감탄사 (헐, ㅋㅋㅋ, 어머나, 얼씨구)
 *
 * C Conjunction: 접속사
 *
 * j SubstantiveJosa: 조사 (의, 에, 에서)
 * l AdverbialJosa: 부사격 조사 (~인, ~의, ~일)
 * e Eomi: 어말어미 (다, 요, 여, 하댘ㅋㅋ)
 * r PreEomi: 선어말어미 (었)
 *
 * p NounPrefix: 접두사 ('초'대박)
 * v VerbPrefix: 동사 접두어 ('쳐'먹어)
 * s Suffix: 접미사 (~적)
 *
 * f Foreign: 한글이 아닌 문자들
 *
 * 지시사는 Derterminant로 대체하기로 함
 * Derterminant is used for demonstratives.
 *
 * Korean: Korean chunk (candidate for parsing)
 * Foreign: Mixture of non-Korean strings
 * Number: 숫자
 * Emotion: Korean Single Character Emotions (ㅋㅋㅋㅋ, ㅎㅎㅎㅎ, ㅠㅜㅠㅜ)
 * Alpha: Alphabets 알파벳
 * Punctuation: 문장부호
 * Hashtag: Twitter Hashtag 해쉬태그 #Korean
 * ScreenName: Twitter username (@nlpenguin)
 *
 * Unkown: Could not parse the string.
 */

#define cmap(arg) {KoreanPos::arg, #arg}

namespace OpenKorean {
enum class KoreanPos {
    // Word leved POS
    Noun, Verb, Adjective, 
    Adverb, Determiner, Exclamation,
    Josa, Eomi, PreEomi, Conjunction,
    Modifier, VerbPrefix, Suffix, Unknown,

    // Chunk level POS
    Korean, Foreign, Number, KoreanParticle, Alpha,
    Punctuation, Hashtag, ScreenName,
    Email, URL, CashTag,

    // Functional POS
    Space, Others,

    ProperNoun,

    //추가
    SpamNouns, FamilyName, GivenName, FullName
};

static const std::set<KoreanPos> OtherPoses = {
    KoreanPos::Korean, KoreanPos::Foreign, KoreanPos::Number, KoreanPos::KoreanParticle, KoreanPos::Alpha,
    KoreanPos::Punctuation, KoreanPos::Hashtag, KoreanPos::ScreenName,
    KoreanPos::Email, KoreanPos::URL, KoreanPos::CashTag
};

static const std::map<KoreanPos,std::string> TagString = {
    cmap(Noun), cmap(Verb), cmap(Adjective), cmap(Adverb), cmap(Determiner), cmap(Exclamation), cmap(Josa),
    cmap(Eomi), cmap(PreEomi), cmap(Conjunction), cmap(Modifier), cmap(VerbPrefix), cmap(Suffix), cmap(Unknown),

    cmap(Korean), cmap(Foreign), cmap(Number), cmap(KoreanParticle), cmap(Alpha),
    cmap(Punctuation), cmap(Hashtag), cmap(ScreenName), cmap(Email), cmap(URL), cmap(CashTag),

    cmap(Space), cmap(Others), cmap(ProperNoun),
    cmap(SpamNouns), cmap(FamilyName), cmap(GivenName), cmap(FullName)
};

static const std::map<char, KoreanPos> shortCut = {
    {'N',KoreanPos::Noun},
    {'V',KoreanPos::Verb},
    {'J',KoreanPos::Adjective},
    {'A',KoreanPos::Adverb},
    {'D',KoreanPos::Determiner},
    {'E',KoreanPos::Exclamation},
    {'C',KoreanPos::Conjunction},

    {'j',KoreanPos::Josa},
    {'e',KoreanPos::Eomi},
    {'r',KoreanPos::PreEomi},
    {'m',KoreanPos::Modifier},
    {'v',KoreanPos::VerbPrefix},
    {'s',KoreanPos::Suffix},

    {'a',KoreanPos::Alpha},
    {'n',KoreanPos::Number},

    {'o',KoreanPos::Others}
};

/*
case class KoreanPosTrie(curPos: KoreanPos, nextTrie: List[KoreanPosTrie], ending: Option[KoreanPos])

  val selfNode = KoreanPosTrie(null, null, ending = None)

  protected[processor] def buildTrie(s: String, ending_pos: KoreanPos): List[KoreanPosTrie] = {
    def isFinal(rest: String): Boolean = {
      val isNextOptional = rest.foldLeft(true) {
        case (output: Boolean, c: Char) if c == '+' || c == '1' => false
        case (output: Boolean, c: Char) => output
      }
      rest.length == 0 || isNextOptional
    }

    if (s.length < 2) {
      return List()
    }

    val pos = shortCut(s.charAt(0))
    val rule = s.charAt(1)
    val rest = s.slice(2, s.length)

    val end: Option[KoreanPos] = if (isFinal(rest)) Some(ending_pos) else None

    rule match {
      case '+' =>
        List(KoreanPosTrie(pos, selfNode :: buildTrie(rest, ending_pos), end))
      case '*' =>
        List(KoreanPosTrie(pos, selfNode :: buildTrie(rest, ending_pos), end)) ++ buildTrie(rest, ending_pos)
      case '1' =>
        List(KoreanPosTrie(pos, buildTrie(rest, ending_pos), end))
      case '0' =>
        List(KoreanPosTrie(pos, buildTrie(rest, ending_pos), end)) ++ buildTrie(rest, ending_pos)
    }
  }

  protected[processor] def getTrie(sequences: Map[String, KoreanPos]): List[KoreanPosTrie] =
    sequences.foldLeft(List[KoreanPosTrie]()) {
      case (results: List[KoreanPosTrie], (s: String, ending_pos: KoreanPos)) =>
        buildTrie(s, ending_pos) ::: results
    }
*/
static const std::set<KoreanPos> Predicates = {KoreanPos::Verb, KoreanPos::Adjective};
}
#endif