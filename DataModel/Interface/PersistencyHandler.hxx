#pragma once

#include "TFile.h"

#include "DataModel/Global.hxx"

class MACE::DataModel::Interface::PersistencyHandler {
    PersistencyHandler(const PersistencyHandler&) = delete;
    PersistencyHandler& operator=(const PersistencyHandler&) = delete;
protected:
    PersistencyHandler();
    virtual ~PersistencyHandler() = 0;

    virtual void Open(const char* fileName, Option_t* option);
    virtual void Close(Option_t* option = nullptr);

public:
    void SetTreeNameIndexer(Char_t indexer);
    void SetTreeNamePrefixFormat(const TString& prefix);
    void SetTreeNameSuffixFormat(const TString& suffix);

    const TString& GetTreeNamePrefixFormat() { return fTreeNamePrefixFormat; }
    const TString& GetTreeNameSuffixFormat() { return fTreeNameSuffixFormat; }
    TString GetTreeNamePrefix(Long64_t i) { return fPrefixHasIndexer ? (fTreeNamePrefix.first + i + fTreeNamePrefix.second) : fTreeNamePrefixFormat; }
    TString GetTreeNameSuffix(Long64_t i) { return fSuffixHasIndexer ? (fTreeNameSuffix.first + i + fTreeNameSuffix.second) : fTreeNameSuffixFormat; }
    template<class Data_t>
    TString GetTreeName(Long64_t i) { return GetTreeNamePrefix(i) + static_cast<const char*>(Data_t::Name()) + GetTreeNameSuffix(i); }

protected:
    TFile* fFile;

private:
    Char_t                      fTreeNameIndexer = '#';
    TString                     fTreeNamePrefixFormat = "Eve#_";
    TString                     fTreeNameSuffixFormat = "";
    Bool_t                      fPrefixHasIndexer = true;
    Bool_t                      fSuffixHasIndexer = false;
    std::pair<TString, TString> fTreeNamePrefix;
    std::pair<TString, TString> fTreeNameSuffix;
};
