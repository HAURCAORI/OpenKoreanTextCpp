#include <string>
#include <regex>
#include <functional>


typedef std::function<std::wstring(const std::wsmatch&)> stringMatchFunc;
typedef stringMatchFunc::argument_type stringMatchArg;
typedef stringMatchFunc::result_type stringMatchRet;

inline std::wstring replaceAll(const std::wstring& input, std::wregex regex, stringMatchFunc func) {
    std::wstring output;
    output.reserve(input.size());

    auto start = std::wsregex_iterator(input.begin(), input.end(), regex);
    auto end = std::wsregex_iterator();
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
