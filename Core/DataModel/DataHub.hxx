#pragma once

#include <concepts>

#include "TFile.h"

#include "DataModel/Global.hxx"
#include "ObserverPtr.hxx"

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
    template<std::derived_from<Interface::Data> Data_t>
    [[nodiscard]] inline TString GetTreeName(Long64_t treeIndex) const;

    // Find a tree in a root file with name provided by Data_t and DataHub settings.
    // The tree is owned by the file.
    // If not found, the return value is defined by ROOT (usually nullptr).
    template<std::derived_from<Interface::Data> Data_t>
    [[nodiscard]] inline ObserverPtr<TTree> FindTree(TFile& file, Long64_t treeIndex = 0);
    // Create an empty tree with name provided by Data_t and DataHub settings.
    // The tree is owned by shared_ptr.
    template<std::derived_from<Interface::Data> Data_t>
    [[nodiscard]] inline std::shared_ptr<TTree> CreateTree(Long64_t treeIndex = 0);
    // Fill an existed tree with a data vector.
    // The data type to be written in tree is specfied by DataInTree_t.
    // DataInTree_t can be shrunken, which means just a part of column in the data vector will be written.
    //   Note: this feature allows to fill the tree with less but exact columns that the data vector has.
    // Note: there is no static branch infomation for the tree, so
    // user should make sure that DataInTree_t represents exactly the same branches as the tree.
    template<std::derived_from<Interface::Data> DataInTree_t, template<class T> typename Pointer_t, std::derived_from<DataInTree_t> DataInList_t>
    static void FillTree(const std::vector<Pointer_t<DataInList_t>>& dataList, TTree& tree, bool connected = false);
    // The raw pointer version of FillTree.
    template<std::derived_from<Interface::Data> DataInTree_t, std::derived_from<DataInTree_t> DataInList_t>
    static inline void FillTree(const std::vector<DataInList_t*>& dataList, TTree& tree, bool connected = false);
    // Same effect as invoke CreateTree<DataInTree_t>(treeIndex) and FillTree<DataInTree_t>(dataList, tree, true).
    template<std::derived_from<Interface::Data> DataInTree_t, template<class T> typename Pointer_t, std::derived_from<DataInTree_t> DataInList_t>
    [[nodiscard]] inline std::shared_ptr<TTree> CreateAndFillTree(const std::vector<Pointer_t<DataInList_t>>& dataList, Long64_t treeIndex = 0);
    // The raw pointer version of CreateAndFillTree.
    template<std::derived_from<Interface::Data> DataInTree_t, std::derived_from<DataInTree_t> DataInList_t>
    [[nodiscard]] inline std::shared_ptr<TTree> CreateAndFillTree(const std::vector<DataInList_t*>& dataList, Long64_t treeIndex = 0);
    // Create a data vector and fill it with a tree.
    // The data type stores in the data vector is specfied by Data_t.
    // Data_t can be shrunken, which means just a part of branch in the tree will be read.
    //   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    // Note: there is no static branch infomation for the tree, so
    // user should ensure that the tree contains branches which Data_t needs.
    template<std::derived_from<Interface::Data> Data_t>
    [[nodiscard]] static std::vector<std::shared_ptr<Data_t>> CreateAndFillList(TTree& tree, bool connected = false);

private:
    Char_t                      fIndexer = '#';
    TString                     fPrefixFormat = "#_";
    TString                     fSuffixFormat = "";
    Bool_t                      fPrefixHasIndexer = true;
    Bool_t                      fSuffixHasIndexer = false;
    std::pair<TString, TString> fSplitPrefix = { "", "_" };
    std::pair<TString, TString> fSplitSuffix = { "", "" };
};

#include "DataModel/DataHub.ixx"
