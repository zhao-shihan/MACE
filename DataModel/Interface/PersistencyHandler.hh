#pragma once

#include "TFile.h"

#include "DataModel/Global.hh"

class MACE::DataModel::Interface::PersistencyHandler {
    PersistencyHandler(const PersistencyHandler&) = delete;
    PersistencyHandler& operator=(const PersistencyHandler&) = delete;
public:
    PersistencyHandler();
    virtual ~PersistencyHandler() = 0;

protected:
    virtual void Open(const char* fileName, Option_t* option);
    virtual void Close(Option_t* option = nullptr);

public:
    void SetTreeNameIndexer(Char_t indexer);
    void SetTreeNamePrefixFormat(const TString& prefix);
    void SetTreeNameSuffixFormat(const TString& suffix);

    void SetTreeIndex(Long64_t index) { fTreeIndex = index; }
    void NextTree() { ++fTreeIndex; }
    Long64_t GetTreeIndex() { return fTreeIndex; }

    const TString& GetTreeNamePrefixFormat() { return fTreeNamePrefixFormat; }
    const TString& GetTreeNameSuffixFormat() { return fTreeNameSuffixFormat; }
    TString GetTreeNamePrefix() { return fPrefixHasIndexer ? (fTreeNamePrefix.first + fTreeIndex + fTreeNamePrefix.second) : fTreeNamePrefixFormat; }
    TString GetTreeNameSuffix() { return fSuffixHasIndexer ? (fTreeNameSuffix.first + fTreeIndex + fTreeNameSuffix.second) : fTreeNameSuffixFormat; }
    template<class DataType>
    TString GetTreeName() { return GetTreeNamePrefix() + static_cast<const char*>(DataType::Name()) + GetTreeNameSuffix(); }

protected:
    TFile* fFile;

private:
    Char_t                      fTreeNameIndexer;
    Long64_t                    fTreeIndex;
    TString                     fTreeNamePrefixFormat;
    TString                     fTreeNameSuffixFormat;
    Bool_t                      fPrefixHasIndexer;
    Bool_t                      fSuffixHasIndexer;
    std::pair<TString, TString> fTreeNamePrefix;
    std::pair<TString, TString> fTreeNameSuffix;
};