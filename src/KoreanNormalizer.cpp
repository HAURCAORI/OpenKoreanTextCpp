#include "KoreanNormalizer.hpp"
#include <functional>

typedef std::function<std::string(const std::string&)> FType;
std::string replaceAll(const std::string& input, std::regex regex, FType func) {
    std::string output;
    
    auto start = std::sregex_iterator(input.begin(), input.end(), regex);
    auto end = std::sregex_iterator();
    while(start != end) {
        output += start->prefix().str();
        output += func(start->str());
        ++start;
    }
    
    return output;
}

namespace OpenKorean {
    const std::regex EXTENTED_KOREAN_REGEX = std::regex(R"(([ㄱ-ㅣ가-힣]+))");
    const std::regex KOREAN_TO_NORMALIZE_REGEX = std::regex(R"(([가-힣]+)(ㅋ+|ㅎ+|[ㅠㅜ]+))");
    const std::regex REPEATING_CHAR_REGEX = std::regex(R"((.)\1{3,}|[ㅠㅜ]{3,})");
    const std::regex REPEATING_2CHAR_REGEX = std::regex(R"((..)\1{2,})");
    const std::regex WHITESPACE_REGEX = std::regex(R"(\s+)");
    const std::vector<std::string> CODA_N_EXCPETION = {"은","는","운","인","텐","근","른","픈","닌","든","던"};

    static std::string normalizeKoreanChunk(const std::string& input) {
        std::string a = "test";
        return a;
    }

    std::string KoreanNormalizer::normalize(const std::string& input) {
        std::string output = replaceAll(input,EXTENTED_KOREAN_REGEX, normalizeKoreanChunk);

        std::cout << output << std::endl;
        //std::replace(input,EXTENTED_KOREAN_REGEX,normalizeKoreanChunk())
        return output;
    }
    
}