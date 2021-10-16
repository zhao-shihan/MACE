#include "DataModel/TreeNameHandler.hh"

using namespace MACE::DataModel;

Char_t                      TreeNameHandler::fgIndexer = '#';
Long64_t                    TreeNameHandler::fgIndex = 0LL;
TString                     TreeNameHandler::fgPrefixFormat = "Eve#_";
TString                     TreeNameHandler::fgSuffixFormat = "";
Bool_t                      TreeNameHandler::fgPrefixHasIndexer = true;
Bool_t                      TreeNameHandler::fgSuffixHasIndexer = false;
std::pair<TString, TString> TreeNameHandler::fgPrefix = { "Eve", "_" };
std::pair<TString, TString> TreeNameHandler::fgSuffix = { "", "" };

void TreeNameHandler::SetIndexer(Char_t indexer) {
    fgIndexer = indexer;
    fgPrefixHasIndexer = Split(fgPrefixFormat, fgPrefix);
    fgSuffixHasIndexer = Split(fgSuffixFormat, fgSuffix);
}

void TreeNameHandler::SetPrefixFormat(const TString& prefix) {
    fgPrefixFormat = prefix;
    fgPrefixHasIndexer = Split(fgPrefixFormat, fgPrefix);
}

void TreeNameHandler::SetSuffixFormat(const TString& suffix) {
    fgSuffixFormat = suffix;
    fgSuffixHasIndexer = Split(fgSuffixFormat, fgSuffix);
}

Bool_t TreeNameHandler::Split(const TString& format, std::pair<TString, TString>& result) {
    auto index = format.First(fgIndexer);
    if (index == kNPOS) {
        result = std::make_pair<TString, TString>(TString(format), TString(""));
        return false;
    } else {
        result = std::make_pair<TString, TString>(format(0, index), format(index + 1, format.Length() - index - 1));
        return true;
    }
}