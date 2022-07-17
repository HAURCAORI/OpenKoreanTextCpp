#pragma once
#include <iostream>

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "KoreanPos.hpp"
#include "KoreanConjugation.hpp"

// files exit process 
#if defined(__linux__) || defined(__unix__)
#include <sys/stat.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <unistd.h>
#else
#error Not Compatible With This OS
#endif

#define RESOURCE_DIR "./resources/"

typedef std::vector<std::string> FilePaths;
namespace OpenKorean {
class KoreanDictionaryProvider {
private:
    static const std::map<KoreanPos,FilePaths> DataPaths;
    
    std::unordered_map<KoreanPos, Dictionary> koreanDictionary;
    std::unordered_map<std::wstring, float> koreanEntityFreq;
    //typoDictionaryByLength
    //predicateStems

    bool isloaded = false;
    void readStreamByLine(std::string filename);
    void readWordFreqs();
    void readWordMap();
    
    //readWordAsSeq
    std::vector<std::wstring> readWordsAsVector(const FilePaths& filenames);
    Dictionary readWords(const FilePaths& filenames);
    //readFileByLineFromResources

#if defined(__linux__) || defined(__unix__)
    inline bool fileExist(const std::string& filename) {
        struct stat buffer;   
        return (stat(filename.c_str(), &buffer) == 0); 
    }
#elif defined(_WIN32) || defined(_WIN64)
    inline bool fileExist(const std::string& filename) {
        return (access(filename.c_str(), F_OK ) != -1);
    }
#endif

public:
    KoreanDictionaryProvider();

    bool fileCheck();
    void load();
    void clear();
    
    inline Dictionary getDictionary(KoreanPos tag) const {
        if(!isloaded) { throw std::runtime_error("Dictionary not loaded."); }
        return (koreanDictionary.find(tag)->second);
    }
    inline bool contain(KoreanPos tag, const std::wstring& str) {
        if(!isloaded) { throw std::runtime_error("Dictionary not loaded."); }
        auto m = koreanDictionary.find(tag);
        if(m == koreanDictionary.end()) { return false; }
        return (m->second.find(str) != m->second.end()) ? true : false;
    }

    //addWordsToDictionary
    //removeWordsToDictionary
    
};
}