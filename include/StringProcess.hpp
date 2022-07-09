#include <string>
#include <regex>
#include <functional>


typedef std::function<std::wstring(const std::wsmatch&)> wstringMatchFunc;
typedef wstringMatchFunc::argument_type wstringMatchArg;
typedef wstringMatchFunc::result_type wstringMatchRet;

inline std::wstring replaceAll(const std::wstring& input, std::wregex regex, wstringMatchFunc func) {
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
inline std::wstring replaceAll(std::wstring input, std::wregex regex, wstringMatchFunc func) {
    std::wstring output;
    std::wsmatch match;
    while(std::regex_search(input, match, regex)) {
        output += match.prefix().str();
        output += func(match);
        input = match.suffix().str();
    }
    return output;
}
*/
