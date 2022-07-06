#include <iostream>
#include "OpenKoreanTextProcessor.hpp"

int main() {
    std::cout << "a" << std::endl;
    OpenKorean::OpenKoreanTextProcessor m;
    std::string text = "abc가나다라 마바사";
    m.normalize(text);
    return 0;
}