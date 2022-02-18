#pragma once

#include "TFile.h"

#include "DataModel/Global.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::DataModel::DataHub final {
public:
    DataHub() = default;
    ~DataHub() noexcept = default;
    DataHub(const DataHub&) = delete;
    DataHub& operator=(const DataHub&) = delete;

    void SetIndexerOfTreeName(Char_t indexer);
    void SetPrefixFormatOfTreeName(const TString& prefix);
    void SetSuffixFormatOfTreeName(const TString& suffix);

    [[nodiscard]] Char_t GetIndexerOfTreeName() const { return fIndexer; }
    [[nodiscard]] const TString& GetPrefixFormatOfTreeName() const { return fPrefixFormat; }
    [[nodiscard]] const TString& GetSuffixFormatOfTreeName() const { return fSuffixFormat; }
    [[nodiscard]] TString GetPrefixOfTreeName(Long64_t i) const { return fPrefixHasIndexer ? (fSplitPrefix.first + i + fSplitPrefix.second) : fPrefixFormat; }
    [[nodiscard]] TString GetSuffixOfTreeName(Long64_t i) const { return fSuffixHasIndexer ? (fSplitSuffix.first + i + fSplitSuffix.second) : fSuffixFormat; }
    template<class Data_t>
    [[nodiscard]] TString GetTreeName(Long64_t treeIndex) const;

    template<class Data_t>
    [[nodiscard]] inline ObserverPtr<TTree> FindTree(TFile& file, Long64_t treeIndex = 0);
    template<class Data_t>
    [[nodiscard]] inline ObserverPtr<TTree> FindTree(const std::unique_ptr<TFile>& file, Long64_t treeIndex = 0);
    template<class Data_t>
    [[nodiscard]] inline ObserverPtr<TTree> FindTree(const std::shared_ptr<TFile>& file, Long64_t treeIndex = 0);
    template<class Data_t>
    [[nodiscard]] inline ObserverPtr<TTree> FindTree(TFile* file, Long64_t treeIndex = 0);

    template<class DataInList_t, class DataInTree_t = DataInList_t>
    [[nodiscard]] inline std::shared_ptr<TTree> CreateTree(const std::vector<std::shared_ptr<DataInList_t>>& dataList, Long64_t treeIndex = 0);
    template<class DataInList_t, class DataInTree_t = DataInList_t>
    [[nodiscard]] inline std::shared_ptr<TTree> CreateTree(const std::vector<std::shared_ptr<const DataInList_t>>& dataList, Long64_t treeIndex = 0);
    template<class DataInList_t, class DataInTree_t = DataInList_t>
    [[nodiscard]] inline std::shared_ptr<TTree> CreateTree(const std::vector<DataInList_t*>& dataList, Long64_t treeIndex = 0);
    template<class DataInList_t, class DataInTree_t = DataInList_t>
    [[nodiscard]] inline std::shared_ptr<TTree> CreateTree(const std::vector<const DataInList_t*>& dataList, Long64_t treeIndex = 0);

    template<class DataInTree_t, class DataInList_t = DataInTree_t>
    [[nodiscard]] static std::vector<std::shared_ptr<DataInList_t>> CreateList(TTree& tree);
    template<class DataInTree_t, class DataInList_t = DataInTree_t>
    [[nodiscard]] static inline std::vector<std::shared_ptr<DataInList_t>> CreateList(const std::unique_ptr<TTree>& tree);
    template<class DataInTree_t, class DataInList_t = DataInTree_t>
    [[nodiscard]] static inline std::vector<std::shared_ptr<DataInList_t>> CreateList(const std::shared_ptr<TTree>& tree);
    template<class DataInTree_t, class DataInList_t = DataInTree_t>
    [[nodiscard]] static inline std::vector<std::shared_ptr<DataInList_t>> CreateList(TTree* tree);

private:
    template<class DataInList_t, class DataInTree_t, class PointerOfDataInList_t>
    [[nodiscard]] std::shared_ptr<TTree> CreateTreeCore(const std::vector<PointerOfDataInList_t>& dataList, Long64_t treeIndex);

private:
    Char_t                      fIndexer = '#';
    TString                     fPrefixFormat = "Eve#_";
    TString                     fSuffixFormat = "";
    Bool_t                      fPrefixHasIndexer = true;
    Bool_t                      fSuffixHasIndexer = false;
    std::pair<TString, TString> fSplitPrefix = { "Eve", "_" };
    std::pair<TString, TString> fSplitSuffix = { "", "" };
};

#include "DataModel/DataHub.ixx"
