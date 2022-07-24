#include "ParsedChunk.hpp"

using namespace OpenKorean;
const std::set<KoreanPos::KoreanPosEnum> ParsedChunk::suffixes = { KoreanPos::KoreanPosEnum::Suffix, KoreanPos::KoreanPosEnum::Eomi, KoreanPos::KoreanPosEnum::Josa, KoreanPos::KoreanPosEnum::PreEomi };
const std::set<KoreanPos::KoreanPosEnum> ParsedChunk::preferredBeforeHaVerb = { KoreanPos::KoreanPosEnum::Noun, KoreanPos::KoreanPosEnum::ProperNoun, KoreanPos::KoreanPosEnum::VerbPrefix };

const std::set<std::wstring> ParsedChunk::josaCheck_1 = {L"는", L"를", L"다"};
const std::set<std::wstring> ParsedChunk::josaCheck_2 = {L"은", L"을", L"이"};