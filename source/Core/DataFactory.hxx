#pragma once

#include "Core/DataModel/ITransientData.hxx"
#include "Utility/ObserverPtr.hxx"

#include "TChain.h"
#include "TFile.h"

#include <filesystem>

namespace MACE::Core {

using DataModel::IsTransientData;
using Utility::ObserverPtr;

class DataFactory final {
public:
    DataFactory() = default;
    ~DataFactory() noexcept = default;
    DataFactory(const DataFactory&) = delete;
    DataFactory& operator=(const DataFactory&) = delete;

    void SetIndexerOfTreeName(Char_t indexer);
    void SetPrefixFormatOfTreeName(const TString& prefix);
    void SetSuffixFormatOfTreeName(const TString& suffix);

    Char_t GetIndexerOfTreeName() const { return fIndexer; }
    const TString& GetPrefixFormatOfTreeName() const { return fPrefixFormat; }
    const TString& GetSuffixFormatOfTreeName() const { return fSuffixFormat; }
    TString GetPrefixOfTreeName(Long64_t i) const { return fPrefixHasIndexer ? (fSplitPrefix.first + i + fSplitPrefix.second) : fPrefixFormat; }
    TString GetSuffixOfTreeName(Long64_t i) const { return fSuffixHasIndexer ? (fSplitSuffix.first + i + fSplitSuffix.second) : fSuffixFormat; }
    template<IsTransientData Data_t>
    TString GetTreeName(Long64_t treeIndex) const;

    /// Find a tree in a root file with name provided by Data_t and DataFactory settings.
    /// The tree is owned by the file.
    /// If not found, the return value is defined by ROOT (usually nullptr).
    template<IsTransientData Data_t>
    ObserverPtr<TTree> GetTree(TFile& file, Long64_t treeIndex = 0) const;
    /// Create a TChain of the list of ROOT files.
    template<IsTransientData Data_t, std::convertible_to<std::filesystem::path::string_type> Path_t>
    std::shared_ptr<TChain> CreateChain(const std::vector<Path_t>& fileList, Long64_t treeIndex = 0) const;
    /// Get the range of tree index in current tree name setting.
    template<IsTransientData Data_t>
    std::pair<Long64_t, Long64_t> GetTreeIndexRange(TFile& file) const;
    /// Create an empty tree with name provided by Data_t and DataFactory settings.
    /// The tree is owned by shared_ptr.
    template<IsTransientData Data_t>
    std::shared_ptr<TTree> CreateTree(Long64_t treeIndex = 0) const;
    /// Fill an existed tree with a data vector.
    /// The data type to be written in tree is specfied by DataInTree_t.
    /// DataInTree_t can be shrunken, which means just a part of column in the data vector will be written.
    ///   Note: this feature allows to fill the tree with less but exact columns that the data vector has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should make sure that DataInTree_t represents exactly the same branches as the tree.
    template<IsTransientData DataInTree_t, template<class T> typename Pointer_t, std::derived_from<DataInTree_t> DataInList_t>
    static void FillTree(const std::vector<Pointer_t<DataInList_t>>& dataList, TTree& tree, bool connected = false);
    /// The raw pointer version of FillTree.
    /// Fill an existed tree with a data vector.
    /// The data type to be written in tree is specfied by DataInTree_t.
    /// DataInTree_t can be shrunken, which means just a part of column in the data vector will be written.
    ///   Note: this feature allows to fill the tree with less but exact columns that the data vector has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should make sure that DataInTree_t represents exactly the same branches as the tree.
    template<IsTransientData DataInTree_t, std::derived_from<DataInTree_t> DataInList_t>
    static void FillTree(const std::vector<DataInList_t*>& dataList, TTree& tree, bool connected = false);
    /// Same effect as invoke CreateTree<DataInTree_t>(treeIndex) and FillTree<DataInTree_t>(dataList, tree, true).
    template<IsTransientData DataInTree_t, template<class T> typename Pointer_t, std::derived_from<DataInTree_t> DataInList_t>
    std::shared_ptr<TTree> CreateAndFillTree(const std::vector<Pointer_t<DataInList_t>>& dataList, Long64_t treeIndex = 0) const;
    /// The raw pointer version of CreateAndFillTree.
    /// Same effect as invoke CreateTree<DataInTree_t>(treeIndex) and FillTree<DataInTree_t>(dataList, tree, true).
    template<IsTransientData DataInTree_t, std::derived_from<DataInTree_t> DataInList_t>
    std::shared_ptr<TTree> CreateAndFillTree(const std::vector<DataInList_t*>& dataList, Long64_t treeIndex = 0) const;
    /// Create a data vector and fill it with a tree.
    /// Entries to be filled are determined by [entriesRange.first, entriesRange.second).
    /// The data type stores in the data vector is specfied by Data_t.
    /// Data_t can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which Data_t needs.
    /// It's user's responsibility to ensure the availability of entriesRange.
    template<IsTransientData Data_t>
    static std::vector<std::shared_ptr<Data_t>> CreateAndFillList(TTree& tree, const std::pair<Long64_t, Long64_t>& entriesRange, bool connected = false);
    /// Create a data vector and fill it with a tree.
    /// The data type stores in the data vector is specfied by Data_t.
    /// Data_t can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which Data_t needs.
    template<IsTransientData Data_t>
    static std::vector<std::shared_ptr<Data_t>> CreateAndFillList(TTree& tree, bool connected = false);
    /// Create a data vector and fill it with a tree. The tree is get via GetTree(TFile& file, Long64_t treeIndex).
    /// Entries to be filled are determined by [entriesRange.first, entriesRange.second).
    /// The data type stores in the data vector is specfied by Data_t.
    /// Data_t can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which Data_t needs.
    /// It's user's responsibility to ensure the availability of entriesRange.
    template<IsTransientData Data_t>
    std::vector<std::shared_ptr<Data_t>> CreateAndFillList(TFile& file, const std::pair<Long64_t, Long64_t>& entriesRange, Long64_t treeIndex = 0, bool connected = false) const;
    /// Create a data vector and fill it with a tree. The tree is get via GetTree(TFile& file, Long64_t treeIndex).
    /// The data type stores in the data vector is specfied by Data_t.
    /// Data_t can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which Data_t needs.
    template<IsTransientData Data_t>
    std::vector<std::shared_ptr<Data_t>> CreateAndFillList(TFile& file, Long64_t treeIndex = 0, bool connected = false) const;

private:
    Char_t fIndexer = '#';
    TString fPrefixFormat = "#_";
    TString fSuffixFormat = "";
    Bool_t fPrefixHasIndexer = true;
    Bool_t fSuffixHasIndexer = false;
    std::pair<TString, TString> fSplitPrefix = {"", "_"};
    std::pair<TString, TString> fSplitSuffix = {"", ""};
};

} // namespace MACE::Core

#include "Core/DataFactory.ixx"
