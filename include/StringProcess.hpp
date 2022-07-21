#include <string>
#include <regex>
#include <functional>

#include <codecvt>
#include <locale>

using wstringMatchFunc = std::function<std::wstring(const std::wsmatch&)>;
using wstringMatchArg = wstringMatchFunc::argument_type;
using wstringMatchRet = wstringMatchFunc::result_type;

inline std::wstring replaceAll(const std::wstring& input, std::wregex regex, wstringMatchFunc func) {
    auto start = std::wsregex_iterator(input.begin(), input.end(), regex);
    auto end = std::wsregex_iterator();
    if(start == end) { return input; } // 매칭 결과가 없을 시 
    
    std::wstring output;
    output.reserve(input.size());
    while(start != end) {
        output += start->prefix().str();
        output += func((*start));
        ++start;
    }
    return output;
}
inline std::wstring convert_wstring(const std::string& str) {
    std::wstring temp(str.begin(),str.end());
    return temp;
}

inline std::wstring takeRight(const std::wstring& str) {
    return std::wstring(1, str.back());
}

inline std::wstring takeRight(const std::wstring& str, size_t num) {
    return str.substr((str.length() > num ) ? (str.length() - num) : 0 );
}

inline std::wstring take(const std::wstring& str, size_t num) {
    return str.substr(0, (str.length() > num) ? num : str.length() );
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
