#pragma once

#include "DataModel/Global.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::DataModel::TreeProvider final {
public:
    TreeProvider() = default;
    ~TreeProvider() noexcept = default;
    TreeProvider(const TreeProvider&) = delete;
    TreeProvider& operator=(const TreeProvider&) = delete;

    void SetIndexerOfTreeName(Char_t indexer);
    void SetPrefixFormatOfTreeName(const TString& prefix);
    void SetSuffixFormatOfTreeName(const TString& suffix);

    Char_t GetIndexerOfTreeName() const { return fIndexer; }
    const TString& GetPrefixFormatOfTreeName() const { return fPrefixFormat; }
    const TString& GetSuffixFormatOfTreeName() const { return fSuffixFormat; }
    TString GetPrefixOfTreeName(Long64_t i) const { return fPrefixHasIndexer ? (fSplitPrefix.first + i + fSplitPrefix.second) : fPrefixFormat; }
    TString GetSuffixOfTreeName(Long64_t i) const { return fSuffixHasIndexer ? (fSplitSuffix.first + i + fSplitSuffix.second) : fSuffixFormat; }
    template<class Data_t>
    [[nodiscard]] TString GetFullTreeName(Long64_t i) const { return GetPrefixOfTreeName(i) + static_cast<const char*>(Data_t::Name()) + GetSuffixOfTreeName(i); }

    template<class Data_t>
    [[nodiscard]] inline ObserverPtr<TTree> FindTree(const std::unique_ptr<TFile>& file, Long64_t treeIndex = 0);
    template<class Data_t>
    [[nodiscard]] inline ObserverPtr<TTree> FindTree(const std::shared_ptr<TFile>& file, Long64_t treeIndex = 0);
    template<class Data_t>
    [[nodiscard]] inline ObserverPtr<TTree> FindTree(TFile* file, Long64_t treeIndex = 0);

    template<class DataInTree_t, class DataInList_t>
    [[nodiscard]] inline std::shared_ptr<TTree> CreateTree(const std::vector<std::shared_ptr<DataInList_t>>& dataList, Long64_t treeIndex = 0);
    template<class DataInTree_t, class DataInList_t>
    [[nodiscard]] inline std::shared_ptr<TTree> CreateTree(const std::vector<std::shared_ptr<const DataInList_t>>& dataList, Long64_t treeIndex = 0);
    template<class DataInTree_t, class DataInList_t>
    [[nodiscard]] inline std::shared_ptr<TTree> CreateTree(const std::vector<DataInList_t*>& dataList, Long64_t treeIndex = 0);
    template<class DataInTree_t, class DataInList_t>
    [[nodiscard]] inline std::shared_ptr<TTree> CreateTree(const std::vector<const DataInList_t*>& dataList, Long64_t treeIndex = 0);

private:
    template<class Data_t, typename PointerOfFile_t>
    [[nodiscard]] inline ObserverPtr<TTree> FindTreeCore(PointerOfFile_t file, Long64_t treeIndex);
    template<class DataInTree_t, class DataInList_t, class PointerOfDataInTree_t>
    [[nodiscard]] std::shared_ptr<TTree> CreateTreeCore(const std::vector<PointerOfDataInTree_t>& dataList, Long64_t treeIndex);

private:
    Char_t                      fIndexer = '#';
    TString                     fPrefixFormat = "Eve#_";
    TString                     fSuffixFormat = "";
    Bool_t                      fPrefixHasIndexer = true;
    Bool_t                      fSuffixHasIndexer = false;
    std::pair<TString, TString> fSplitPrefix = { "Eve", "_" };
    std::pair<TString, TString> fSplitSuffix = { "", "" };
};

#include "DataModel/TreeManager/TreeProvider.ixx"
