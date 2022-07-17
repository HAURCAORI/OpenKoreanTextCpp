//#define ENABLE_LOG
#include "ProcessLog.hpp"
#include "KoreanDictionaryProvider.hpp"
#include "StringProcess.hpp"

//#define TEST_SET


using namespace OpenKorean;

const std::map<KoreanPos,FilePaths> KoreanDictionaryProvider::DataPaths {
#ifdef TEST_SET
    {KoreanPos::Noun, {"noun/test.txt"}}
#else   
    {KoreanPos::Noun, {"noun/nouns.txt", "noun/entities.txt", "noun/spam.txt",
        "noun/names.txt", "noun/twitter.txt", "noun/lol.txt",
        "noun/slangs.txt", "noun/company_names.txt",
        "noun/foreign.txt", "noun/geolocations.txt", "noun/profane.txt",
        "substantives/given_names.txt", "noun/kpop.txt", "noun/bible.txt",
        "noun/pokemon.txt", "noun/congress.txt", "noun/wikipedia_title_nouns.txt",
        "noun/brand.txt", "noun/fashion.txt", "noun/neologism.txt"}},
    {KoreanPos::Verb, {"verb/verb.txt"}},
    {KoreanPos::Adjective, {"adjective/adjective.txt"}},
    {KoreanPos::Adverb, {"adverb/adverb.txt"}},
    {KoreanPos::Determiner, {"auxiliary/determiner.txt"}},
    {KoreanPos::Exclamation, {"auxiliary/exclamation.txt"}},
    {KoreanPos::Josa, {"josa/josa.txt"}},
    {KoreanPos::Eomi, {"verb/eomi.txt"}},
    {KoreanPos::PreEomi, {"verb/pre_eomi.txt"}},
    {KoreanPos::Conjunction, {"auxiliary/conjunctions.txt"}},
    {KoreanPos::Modifier, {"substantives/modifier.txt"}},
    {KoreanPos::VerbPrefix, {"verb/verb_prefix.txt"}},
    {KoreanPos::Suffix, {"substantives/suffix.txt"}},

    {KoreanPos::ProperNoun, {"noun/entities.txt","noun/names.txt", "noun/twitter.txt", "noun/lol.txt", "noun/company_names.txt",
        "noun/foreign.txt", "noun/geolocations.txt",
        "substantives/given_names.txt", "noun/kpop.txt", "noun/bible.txt",
        "noun/pokemon.txt", "noun/congress.txt", "noun/wikipedia_title_nouns.txt",
        "noun/brand.txt", "noun/fashion.txt", "noun/neologism.txt"}},

    {KoreanPos::SpamNouns, {"noun/spam.txt", "noun/profane.txt"}},

    {KoreanPos::FamilyName, {"substantives/family_names.txt"}},
    {KoreanPos::GivenName, {"substantives/given_names.txt"}},
    {KoreanPos::FullName, {"noun/kpop.txt", "noun/foreign.txt", "noun/names.txt"}}
#endif
};

std::vector<std::wstring> KoreanDictionaryProvider::readWordsAsVector(const FilePaths& filenames) {
    std::vector<std::wstring> temp;
    for(auto iterFile = filenames.begin(); iterFile != filenames.end(); ++iterFile) {
        std::string path = RESOURCE_DIR + *iterFile;
        FILE *fp = fopen(path.c_str(), "r");

        if(fp == NULL) { throw std::ios_base::failure("Error while opening file '" + *iterFile + "'."); }
        wchar_t buffer[50];
        while(fgetws(buffer, 50, fp) != NULL) {
            std::wstring str(buffer);
            str.pop_back();
            temp.push_back(str);
        }
        fclose(fp);
        /*
        char buffer[50];
        while(fgets(buffer, 50, fp) != NULL) {
            std::string str(buffer);
            str.pop_back();
            temp.push_back(convert_wstring(str));
        }
        fclose(fp);*/
    }
    return temp;
}

Dictionary KoreanDictionaryProvider::readWords(const FilePaths& filenames) {
    Dictionary temp;
    for(auto iterFile = filenames.begin(); iterFile != filenames.end(); ++iterFile) {
        std::string path = RESOURCE_DIR + *iterFile;
        FILE *fp = fopen(path.c_str(), "r");

        if(fp == NULL) { throw std::ios_base::failure("Error while opening file '" + *iterFile + "'."); }
        wchar_t buffer[50];
        while(fgetws(buffer, 50, fp) != NULL) {
            std::wstring str(buffer);
            str.pop_back();
            temp.insert(str);
        }
        /*
        char buffer[50];
        while(fgets(buffer, 50, fp) != NULL) {
            std::string str(buffer);
            str.pop_back();
            temp.insert(convert_wstring(str));
        }*/
        fclose(fp);
    }
    return temp;
}


/*
    파일의 존재 유무 확인
*/
bool KoreanDictionaryProvider::fileCheck() {
    ProcessLog::log(ProcessLog::Process,"Dictionary FileCheck...");
    for(auto iterType = DataPaths.begin(); iterType != DataPaths.end(); ++iterType) {
        auto paths = iterType->second;
        for(auto iterPath = paths.begin(); iterPath != paths.end(); ++ iterPath) {
            ProcessLog::logs("file check : " + *iterPath + "...");
            if(fileExist(RESOURCE_DIR + *iterPath)) {
                ProcessLog::log(" OK");
            }else {
                ProcessLog::log(" FAIL");
                return false;
            }
        }
    }
    ProcessLog::log(ProcessLog::Success, "Dictionary FileCheck");
    return true;
}

/*
    파일을 koreanDictionary으로 로드
*/
void KoreanDictionaryProvider::load() {
    if(isloaded) { clear(); }
    if(!fileCheck()) {
        ProcessLog::log(ProcessLog::Error, "Fail to Load");
        return;
    }
    try {
        ProcessLog::log(ProcessLog::Process, "Loading...");
        for(auto iterType = DataPaths.begin(); iterType != DataPaths.end(); ++iterType) {
            ProcessLog::logs("loading : " + TagString.find(iterType->first)->second + "...");
            if(iterType->first == KoreanPos::Verb) {
                koreanDictionary[iterType->first] = KoreanConjugation::conjugatePredicated(readWordsAsVector(iterType->second));
            } else if (iterType->first == KoreanPos::Adjective) {
                koreanDictionary[iterType->first] = KoreanConjugation::conjugatePredicated(readWordsAsVector(iterType->second), true);
            } else {
                koreanDictionary[iterType->first] = readWords(iterType->second);
            }
            ProcessLog::log(" OK");
        }
        ProcessLog::log(ProcessLog::Success, "Loading");
    } catch (const std::ios_base::failure& ex) {
        std::cerr << ex.what() << std::endl;
        ProcessLog::log(ProcessLog::Error, "[Error] Fail to Load");
    }
    isloaded = true;
}

void KoreanDictionaryProvider::clear() {
    koreanEntityFreq.clear();
    koreanDictionary.clear();
}


KoreanDictionaryProvider::KoreanDictionaryProvider() {
    load();
}