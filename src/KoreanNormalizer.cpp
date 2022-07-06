#include "KoreanNormalizer.hpp"

namespace OpenKorean {
    const std::regex EXTENTED_KOREAN_REGEX = std::regex(R"(([ㄱ-ㅣ가-힣]+))");
    const std::regex KOREAN_TO_NORMALIZE_REGEX = std::regex(R"(([가-힣]+)(ㅋ+|ㅎ+|[ㅠㅜ]+))");
    const std::regex REPEATING_CHAR_REGEX = std::regex(R"((.)\1{3,}|[ㅠㅜ]{3,})");
    const std::regex REPEATING_2CHAR_REGEX = std::regex(R"((..)\1{2,})");
    const std::regex WHITESPACE_REGEX = std::regex(R"(\s+)");
    const std::vector<std::string> CODA_N_EXCPETION = {"은","는","운","인","텐","근","른","픈","닌","든","던"};


    std::string KoreanNormalizer::normalize(std::string input) {
        EXTENTED_KOREAN_REGEX
    }
    
}