#include <iostream>
#include <locale>
#include "OpenKoreanTextProcessor.hpp"
#include "KoreanChunker.hpp"

//#include <regex>
//#include <cstddef>

#include <chrono>
#define BEGIN_CHRONO std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
#define END_CHRONO std::wcout << L"Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count() << "[ms]" << std::endl;

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

template<typename T, typename U>
void printMap(std::map<T,U> m) {
    for(auto it = m.begin(); it != m.end(); ++it) {
        std::wcout << it->first << L"/" << it->second << std::endl;
    }
}

void printVec(std::vector<std::wstring> m) {
    for(auto it = m.begin(); it != m.end(); ++it) {
        std::wcout << *it << L"/" << it->length() << std::endl;
    }
}

template<typename T>
std::vector<T> operator*(const std::vector<T>& lhs, const std::vector<T>& rhs) {
    std::vector<T> temp;
    temp.insert(temp.begin(), lhs.begin(), lhs.end());
    temp.insert(temp.end(), rhs.begin(), rhs.end());
    return temp;
}

int main() {
    std::locale::global(std::locale(""));
    //test_conjugation();
    //printMap(OpenKorean::KoreanConjugation::getConjugationMap({ L"가", L"가까워지", L"가꾸", L"가꾸어지", L"가누" },true));

    //auto temp = OpenKorean::KoreanChunker::splitBySpaceKeepingSpace(L" 가나  다라마 바 사아자 ");
    //printVec(temp);

    //OpenKorean::OpenKoreanTextProcessor m;
    //std::wstring text = LR"(슬프뮤ㅠㅠ)";
    //std::wcout << m.normalize(text) << std::endl;

    /*
    std::string ts("가가호호");
    std::wstring ws(ts.begin(), ts.end());
    std::cout << ts << std::endl;
    std::wcout << ws << std::endl;
    std::cout << dic.contain(OpenKorean::KoreanPos::Verb, ws) << std::endl;
    */
    
    return 0;
}