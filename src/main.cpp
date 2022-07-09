#include <iostream>
#include <locale>
#include "OpenKoreanTextProcessor.hpp"

//#include <regex>
//#include <cstddef>

#include <chrono>
#define BEGIN_CHRONO std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
#define END_CHRONO std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count() << "[ms]" << std::endl;

int main() {
    std::locale::global(std::locale(""));
    OpenKorean::OpenKoreanTextProcessor m;


    std::wstring text = LR"(가나다ㅋㅋㅋㅋ)";
    BEGIN_CHRONO
    for(int i = 0; i < 1000; i++)
        m.normalize(text);
    END_CHRONO
    return 0;
}