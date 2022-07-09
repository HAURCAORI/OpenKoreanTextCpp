#include <iostream>
#include "OpenKoreanTextProcessor.hpp"

//#include <regex>
//#include <cstddef>
#include <locale>

int main() {
    OpenKorean::OpenKoreanTextProcessor m;
    std::locale::global(std::locale(""));
    /*
    std::wstring text = LR"(가ㅋㅋㅋㅋㅋ)";
    std::wregex KOREAN_TO_NORMALIZE_REGEX(LR"(([가-힣]+)(ㅋ+|ㅎ+|[ㅠㅜ]+))");
    std::wsmatch ma;
    if(std::regex_search(text,ma,KOREAN_TO_NORMALIZE_REGEX)) {
        std::wcout << text << std::endl;
        std::wcout << LR"(([가-힣]+)(ㅋ+|ㅎ+|[ㅠㅜ]+))" << std::endl;
        std::wcout << ma.str(1) << "/" << ma.str(2) << std::endl;
    }
    */
    std::wstring text = LR"(가ㅋㅋㅋㅋㅋ)";
    m.normalize(text);
    return 0;
}