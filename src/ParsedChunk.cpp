#include "ParsedChunk.hpp"

using namespace OpenKorean;
const std::set<KoreanPos::KoreanPosEnum> suffixes = { KoreanPos::KoreanPosEnum::Suffix, KoreanPos::KoreanPosEnum::Eomi, KoreanPos::KoreanPosEnum::Josa, KoreanPos::KoreanPosEnum::PreEomi };
const std::set<KoreanPos::KoreanPosEnum> preferredBeforeHaVerb = { KoreanPos::KoreanPosEnum::Noun, KoreanPos::KoreanPosEnum::ProperNoun, KoreanPos::KoreanPosEnum::VerbPrefix };

