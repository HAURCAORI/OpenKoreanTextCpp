#include "KoreanDictionaryProvider.hpp"
#include "StringProcess.hpp"
/*
#include <chrono>
#define BEGIN_CHRONO std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
#define END_CHRONO std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count() << "[ms]" << std::endl;
*/

using namespace OpenKorean;

const std::map<KoreanPos,FilePaths> KoreanDictionaryProvider::DataPaths {
    {KoreanPos::Noun, {"noun/test.txt"}}
    /*
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
    */
};


Dictionary KoreanDictionaryProvider::readWords(const FilePaths& filenames) {
    Dictionary temp;
    for(auto iterFile = filenames.begin(); iterFile != filenames.end(); ++iterFile) {
        std::string path = RESOURCE_DIR + *iterFile;
        FILE *fp = fopen(path.c_str(), "r");

        if(fp == NULL) { throw std::ios_base::failure("Error while opening file '" + *iterFile + "'."); }
        char buffer[50];
        while(fgets(buffer, 50, fp) != NULL) {
            temp.insert(convert_wstring(buffer));
        }
        fclose(fp);
        
    }
    //temp.insert();
    return temp;
}


bool KoreanDictionaryProvider::fileCheck() {
    std::cout << "[Process] Dictionary FileCheck..." << std::endl;
    for(auto iterType = DataPaths.begin(); iterType != DataPaths.end(); ++iterType) {
        auto paths = iterType->second;
        for(auto iterPath = paths.begin(); iterPath != paths.end(); ++ iterPath) {
            std::cout << "file check : " << *iterPath << "...";
            if(fileExist(RESOURCE_DIR + *iterPath)) {
                std::cout << " OK" << std::endl;
            }else {
                std::cout << " FAIL" << std::endl;
                return false;
            }
        }
    }
    std::cout << "[Success] Dictionary FileCheck" << std::endl;
    return true;
}

void KoreanDictionaryProvider::load() {
    if(isloaded) { clear(); }
    if(!fileCheck()) {
        std::cerr << "[Error] Fail to Load" << std::endl;
        return;
    }
    try {
        for(auto iterType = DataPaths.begin(); iterType != DataPaths.end(); ++iterType) {
            //BEGIN_CHRONO
            koreanDictionary[iterType->first] = readWords(iterType->second);
            //END_CHRONO
        }
    } catch (const std::ios_base::failure& ex) {
        std::cerr << ex.what() << std::endl;
        std::cerr << "[Error] Fail to Load" << std::endl;
    }
    isloaded = true;
}

void KoreanDictionaryProvider::clear() {
    koreanEntityFreq.clear();
    koreanDictionary.clear();
    spanNouns.clear();
    properNouncs.clear();
    nameDictionary.clear();
}


KoreanDictionaryProvider::KoreanDictionaryProvider() {
    load();
}