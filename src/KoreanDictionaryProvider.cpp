#include "KoreanDictionaryProvider.hpp"
#include <fstream>

using namespace OpenKorean;

const std::map<KoreanPos,FilePaths> KoreanDictionaryProvider::DataPaths {
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
};

KoreanDictionaryProvider::KoreanDictionaryProvider() {
    std::cout << "Dictionary FileCheck..." << std::endl;
    for(auto iterType = DataPaths.begin(); iterType != DataPaths.end(); ++iterType) {
        auto paths = iterType->second;
        for(auto iterPath = paths.begin(); iterPath != paths.end(); ++ iterPath) {
            std::cout << *iterPath << std::endl;
        }
    }
}

Dictionary KoreanDictionaryProvider::readWords(const std::vector<std::string>& filenames) {
    for(auto it = filenames.begin(); it != filenames.end(); ++it) {
        std::wifstream fileData;
        fileData.open(*it);
        if(fileData.fail()) {
            throw std::ios_base::failure("Error while opening file '" + *it + "'.");
        }
    }
}