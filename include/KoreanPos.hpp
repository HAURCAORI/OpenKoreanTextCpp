#pragma once
#include <map>
#include <set>
#include <vector>
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



namespace OpenKorean {

struct KoreanPosTrie;

class KoreanPos {
private:
  static bool isFinal(const std::wstring& rest) {
    bool isNextOptional = [](const std::wstring& rest) {
      bool output = true;
      for(auto it = rest.begin(); it != rest.end(); ++it) {
        if(*it == L'+' || *it == L'1') { output = false; }
      }
      return output;
    };
    return rest.length() == 0 || isNextOptional; 
  }

public:
  enum class KoreanPosEnum {
    Null = 0, 

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
  
  static const std::set<KoreanPosEnum> OtherPoses;
  static const std::map<KoreanPosEnum,std::string> TagString;
  static const std::map<wchar_t, KoreanPosEnum> shortCut;
  static const std::set<KoreanPosEnum> Predicates;
  static std::vector<KoreanPosTrie> buildTrie(const std::wstring& s, KoreanPosEnum ending_pos);
  static std::vector<KoreanPosTrie> getTrie(std::map<std::wstring, KoreanPosEnum> sequences);

  
};

struct KoreanPosTrie {
  KoreanPos::KoreanPosEnum curPos;
  std::vector<KoreanPosTrie> nextTrie;
  KoreanPos::KoreanPosEnum ending;
    
  static KoreanPosTrie selfNode() { return {KoreanPos::KoreanPosEnum::Null, std::vector<KoreanPosTrie>(), KoreanPos::KoreanPosEnum::Null}; }
  static std::vector<KoreanPosTrie>selfNodeVec() { return std::vector<KoreanPosTrie>(1, selfNode()); }

  KoreanPosTrie(KoreanPos::KoreanPosEnum c, const std::vector<KoreanPosTrie> n, KoreanPos::KoreanPosEnum e) : curPos(c), nextTrie(n), ending(e) {}

  bool isSelfNode() {
    return (curPos == KoreanPos::KoreanPosEnum::Null) && (ending == KoreanPos::KoreanPosEnum::Null);
  }
};


}