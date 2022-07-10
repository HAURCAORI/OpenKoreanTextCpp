#include <iostream>
#include <locale>
#include "OpenKoreanTextProcessor.hpp"
#include "KoreanDictionaryProvider.hpp"
//#include <regex>
//#include <cstddef>

#include <chrono>
#define BEGIN_CHRONO std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
#define END_CHRONO std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count() << "[ms]" << std::endl;

int main() {
    std::locale::global(std::locale(""));
    /*
    OpenKorean::OpenKoreanTextProcessor m;

    std::wstring text = LR"(가나다ㅋㅋㅋㅋ)";
    m.normalize(text);
    */
    OpenKorean::KoreanDictionaryProvider dic;
    std::string ts("가가호호");
    std::wstring ws(ts.begin(), ts.end());
    std::cout << ts << std::endl;
    std::wcout << ws << std::endl;
    std::cout << dic.contain(OpenKorean::KoreanPos::Noun, L"가가호호") << std::endl;
    
    return 0;
}