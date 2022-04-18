#include "MACE/Core/DataFactory.hxx"

using MACE::Core::DataFactory;

static Bool_t Split(const TString& format, Char_t indexer, std::pair<TString, TString>& result) {
    auto index = format.First(indexer);
    if (index == kNPOS) {
        result = std::make_pair<TString, TString>(TString(format), TString(""));
        return false;
    } else {
        result = std::make_pair<TString, TString>(format(0, index), format(index + 1, format.Length() - index - 1));
        return true;
    }
}

void DataFactory::SetTreeNameIndexer(Char_t indexer) {
    fIndexer = indexer;
    fPrefixHasIndexer = Split(fPrefixFormat, fIndexer, fSplitPrefix);
    fSuffixHasIndexer = Split(fSuffixFormat, fIndexer, fSplitSuffix);
}

void DataFactory::SetTreeNamePrefixFormat(const TString& prefix) {
    fPrefixFormat = prefix;
    fPrefixHasIndexer = Split(fPrefixFormat, fIndexer, fSplitPrefix);
}

void DataFactory::SetTreeNameSuffixFormat(const TString& suffix) {
    fSuffixFormat = suffix;
    fSuffixHasIndexer = Split(fSuffixFormat, fIndexer, fSplitSuffix);
}
