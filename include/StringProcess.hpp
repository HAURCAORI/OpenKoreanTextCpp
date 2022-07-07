#include <string>
#include <regex>
#include <functional>


typedef std::function<std::string(const std::smatch&)> stringMatchFunc;
typedef stringMatchFunc::argument_type stringMatchArg;
typedef stringMatchFunc::result_type stringMatchRet;

std::string replaceAll(const std::string& input, std::regex regex, stringMatchFunc func) {
    std::string output;
    output.reserve(input.size());

    auto start = std::sregex_iterator(input.begin(), input.end(), regex);
    auto end = std::sregex_iterator();
    while(start != end) {
        output += start->prefix().str();
        output += func((*start));
        ++start;
    }
    return output;
}

/*
std::string replaceAll(std::string input, std::regex regex, stringMatchFunc func) {
    std::string output;
    std::smatch match;
    while(std::regex_search(input, match, regex)) {
        output += match.prefix().str();
        std::cout << match[2] << std::endl;
        output += func(match);
        input = match.suffix().str();
    }
    return output;
}
*/
