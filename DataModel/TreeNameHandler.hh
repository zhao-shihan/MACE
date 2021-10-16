#pragma once

#include "DataModel/Global.hh"

class MACE::DataModel::TreeNameHandler final {
    TreeNameHandler() = delete;
public:
    static void SetIndexer(Char_t indexer);
    static void SetPrefixFormat(const TString& prefix);
    static void SetSuffixFormat(const TString& suffix);

    static void SetIndex(Long64_t index) { fgIndex = index; }
    static void NextIndex() { ++fgIndex; }
    static Long64_t GetIndex() { return fgIndex; }

    static const TString& GetPrefixFormat() { return fgPrefixFormat; }
    static const TString& GetSuffixFormat() { return fgSuffixFormat; }
    static TString GetPrefix() { return fgPrefixHasIndexer ? (fgPrefix.first + fgIndex + fgPrefix.second) : fgPrefixFormat; }
    static TString GetSuffix() { return fgSuffixHasIndexer ? (fgSuffix.first + fgIndex + fgSuffix.second) : fgSuffixFormat; }
    template<class DataType>
    static TString GetName() { return GetPrefix() + static_cast<TString>(DataType::Name()) + GetSuffix(); }

private:
    static Bool_t Split(const TString& format, std::pair<TString, TString>& result);

private:
    static Char_t                      fgIndexer;
    static Long64_t                    fgIndex;
    static TString                     fgPrefixFormat;
    static TString                     fgSuffixFormat;
    static Bool_t                      fgPrefixHasIndexer;
    static Bool_t                      fgSuffixHasIndexer;
    static std::pair<TString, TString> fgPrefix;
    static std::pair<TString, TString> fgSuffix;
};