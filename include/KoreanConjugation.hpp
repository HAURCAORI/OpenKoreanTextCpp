#include "Hangul.hpp"

namespace OpenKorean {

class KoreanConjugation {
private:
    static const std::vector<Char> CODAS_COMMON;
    static const std::vector<Char> CODAS_FOR_CONTRACTION;
    static const std::vector<Char> CODAS_NO_PAST;
    static const std::vector<Char> CODAS_SLANG_CONSONANT;
    static const std::vector<Char> CODAS_SLANG_VOWEL;
    static const std::vector<Char> PRE_EOMI_COMMON;
    static const std::vector<Char> PRE_EOMI_1_1;
    static const std::vector<Char> PRE_EOMI_1_2;
    static const std::vector<Char> PRE_EOMI_1_3;
    static const std::vector<Char> PRE_EOMI_1_4;
    static const std::vector<Char> PRE_EOMI_1_5;

    static const std::vector<Char> PRE_EOMI_2;
    static const std::vector<Char> PRE_EOMI_3;
    static const std::vector<Char> PRE_EOMI_4;
    static const std::vector<Char> PRE_EOMI_5;
    static const std::vector<Char> PRE_EOMI_6;
    static const std::vector<Char> PRE_EOMI_7;

    static const std::vector<Char> PRE_EOMI_RESPECT;

    static const std::vector<Char> PRE_EOMI_VOWEL;
public:
    static std::vector<std::wstring> addPreEomi(Char lastChar, std::vector<Char> charsToAdd) {
        std::vector<std::wstring> ret;
        for(auto it = charsToAdd.begin(); it != charsToAdd.end(); ++it) {
            std::wstring ws(1, lastChar);
            ws.append(1,*it);
            ret.push_back(ws);
        }
        return ret;
    }
};
}