#pragma once

#include "MACE/Core/DataModel/ITransientData.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

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

    void SetTreeNameIndexer(Char_t indexer);
    void SetTreeNamePrefixFormat(const TString& prefix);
    void SetTreeNameSuffixFormat(const TString& suffix);

    Char_t GetTreeNameIndexer() const { return fIndexer; }
    const TString& GetTreeNamePrefixFormat() const { return fPrefixFormat; }
    const TString& GetTreeNameSuffixFormat() const { return fSuffixFormat; }
    TString GetTreeNamePrefix(Long64_t i) const { return fPrefixHasIndexer ? (fSplitPrefix.first + i + fSplitPrefix.second) : fPrefixFormat; }
    TString GetTreeNameSuffix(Long64_t i) const { return fSuffixHasIndexer ? (fSplitSuffix.first + i + fSplitSuffix.second) : fSuffixFormat; }
    template<IsTransientData DataT>
    TString GetTreeName(Long64_t treeIndex) const;

    /// Find a tree in a root file with name provided by DataT and DataFactory settings.
    /// The tree is owned by the file.
    /// If not found, the return value is defined by ROOT (usually nullptr).
    template<IsTransientData DataT>
    ObserverPtr<TTree> GetTree(TFile& file, Long64_t treeIndex = 0) const;
    /// Create a TChain of the list of ROOT files.
    template<IsTransientData DataT, std::convertible_to<std::filesystem::path::string_type> PathT>
    std::shared_ptr<TChain> CreateChain(const std::vector<PathT>& fileList, Long64_t treeIndex = 0) const;
    /// Get the range of tree index in current tree name setting.
    template<IsTransientData DataT>
    std::pair<Long64_t, Long64_t> GetTreeIndexRange(TFile& file) const;
    /// Create an empty tree with name provided by DataT and DataFactory settings.
    /// The tree is owned by shared_ptr.
    template<IsTransientData DataT>
    std::shared_ptr<TTree> CreateTree(Long64_t treeIndex = 0) const;
    /// Fill an existed tree with a data vector.
    /// The data type to be written in tree is specfied by DataInTreeT.
    /// DataInTreeT can be shrunken, which means just a part of column in the data vector will be written.
    ///   Note: this feature allows to fill the tree with less but exact columns that the data vector has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should make sure that DataInTreeT represents exactly the same branches as the tree.
    template<IsTransientData DataInTreeT, template<class T, class... _> typename PointerT, std::derived_from<DataInTreeT> DataInListT>
    static void FillTree(const std::vector<PointerT<DataInListT>>& dataList, TTree& tree, bool connected = false);
    /// The raw pointer version of FillTree.
    /// Fill an existed tree with a data vector.
    /// The data type to be written in tree is specfied by DataInTreeT.
    /// DataInTreeT can be shrunken, which means just a part of column in the data vector will be written.
    ///   Note: this feature allows to fill the tree with less but exact columns that the data vector has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should make sure that DataInTreeT represents exactly the same branches as the tree.
    template<IsTransientData DataInTreeT, std::derived_from<DataInTreeT> DataInListT>
    static void FillTree(const std::vector<DataInListT*>& dataList, TTree& tree, bool connected = false);
    /// Same effect as invoke CreateTree<DataInTreeT>(treeIndex) and FillTree<DataInTreeT>(dataList, tree, true).
    template<IsTransientData DataInTreeT, template<class T, class... _> typename PointerT, std::derived_from<DataInTreeT> DataInListT>
    std::shared_ptr<TTree> CreateAndFillTree(const std::vector<PointerT<DataInListT>>& dataList, Long64_t treeIndex = 0) const;
    /// The raw pointer version of CreateAndFillTree.
    /// Same effect as invoke CreateTree<DataInTreeT>(treeIndex) and FillTree<DataInTreeT>(dataList, tree, true).
    template<IsTransientData DataInTreeT, std::derived_from<DataInTreeT> DataInListT>
    std::shared_ptr<TTree> CreateAndFillTree(const std::vector<DataInListT*>& dataList, Long64_t treeIndex = 0) const;
    /// Create a data vector and fill it with a tree.
    /// Entries to be filled are determined by [entriesRange.first, entriesRange.second).
    /// The data type stores in the data vector is specfied by DataT.
    /// DataT can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which DataT needs.
    /// It's user's responsibility to ensure the availability of entriesRange.
    template<IsTransientData DataT>
    static std::vector<std::shared_ptr<DataT>> CreateAndFillList(TTree& tree, const std::pair<Long64_t, Long64_t>& entriesRange, bool connected = false);
    /// Create a data vector and fill it with a tree.
    /// The data type stores in the data vector is specfied by DataT.
    /// DataT can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which DataT needs.
    template<IsTransientData DataT>
    static std::vector<std::shared_ptr<DataT>> CreateAndFillList(TTree& tree, bool connected = false);
    /// Create a data vector and fill it with a tree. The tree is get via GetTree(TFile& file, Long64_t treeIndex).
    /// Entries to be filled are determined by [entriesRange.first, entriesRange.second).
    /// The data type stores in the data vector is specfied by DataT.
    /// DataT can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which DataT needs.
    /// It's user's responsibility to ensure the availability of entriesRange.
    template<IsTransientData DataT>
    std::vector<std::shared_ptr<DataT>> CreateAndFillList(TFile& file, const std::pair<Long64_t, Long64_t>& entriesRange, Long64_t treeIndex = 0, bool connected = false) const;
    /// Create a data vector and fill it with a tree. The tree is get via GetTree(TFile& file, Long64_t treeIndex).
    /// The data type stores in the data vector is specfied by DataT.
    /// DataT can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which DataT needs.
    template<IsTransientData DataT>
    std::vector<std::shared_ptr<DataT>> CreateAndFillList(TFile& file, Long64_t treeIndex = 0, bool connected = false) const;

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

#include "MACE/Core/DataFactory.ixx"
