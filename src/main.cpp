#include <iostream>
#include "OpenKoreanTextProcessor.hpp"

int main() {
    OpenKorean::OpenKoreanTextProcessor m;
    std::string text = "가나다라ㅋㅋㅋㅋㅋ 마바사ㅋㅋㅋㅋㅋ";
    m.normalize(text);
    return 0;
}