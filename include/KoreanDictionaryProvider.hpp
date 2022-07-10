#include <iostream>

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <KoreanPos.hpp>

#define RESOURCE_DIR "./resources/"

typedef std::unordered_set<std::wstring> Dictionary;
typedef std::vector<std::string> FilePaths;
namespace OpenKorean {
class KoreanDictionaryProvider {
private:
    static const std::map<KoreanPos,FilePaths> DataPaths;
    
    std::unordered_map<std::wstring, float> koreanEntityFreq;
    std::unordered_map<KoreanPos, Dictionary> koreanDictionary;
    
    Dictionary spanNouns;
    Dictionary properNouncs;
    std::unordered_map<std::wstring, Dictionary>nameDictionary;
    //typoDictionaryByLength
    //predicateStems


    void readStreamByLine(std::string filename);
    void readWordFreqs();
    void readWordMap();
    
    //readWordAsSeq
    //readWordAsSet
    Dictionary readWords(const std::vector<std::string>& filenames);
    //readFileByLineFromResources

public:
    KoreanDictionaryProvider();
    //addWordsToDictionary
    //removeWordsToDictionary
};
}