#include <iostream>
#include <locale>
#include "OpenKoreanTextProcessor.hpp"
#include "KoreanConjugation.hpp"
//#include <regex>
//#include <cstddef>

#include <chrono>
#define BEGIN_CHRONO std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
#define END_CHRONO std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count() << "[ms]" << std::endl;

void test_conjugation() {
    std::wcout << L"test1" << std::endl;
    auto temp = OpenKorean::KoreanConjugation::addPreEomi(L'가', {L'앗',L'었'});
    for(auto it = temp.begin(); it != temp.end(); ++it) {
        std::wcout << *it << std::endl;
    }
    std::wcout << L"test2" << std::endl;
    auto temp2 = OpenKorean::KoreanConjugation::conjugatePredicated(L"아니",true);
    for(auto it = temp2.begin(); it != temp2.end(); ++it) {
        std::wcout << *it << std::endl;
    }
}

int main() {
    std::locale::global(std::locale(""));
    
    //test_conjugation();

    OpenKorean::OpenKoreanTextProcessor m;
    std::wstring text = LR"(가나다ㅋㅋㅋㅋ)";

    std::wcout << m.normalize(text) << std::endl;
    
    /*
    std::string ts("가가호호");
    std::wstring ws(ts.begin(), ts.end());
    std::cout << ts << std::endl;
    std::wcout << ws << std::endl;
    std::cout << dic.contain(OpenKorean::KoreanPos::Verb, ws) << std::endl;
    */
    
    return 0;
}