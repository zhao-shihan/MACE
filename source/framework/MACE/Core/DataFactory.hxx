#pragma once

#include "MACE/Concept/PointerImitator.hxx"
#include "MACE/Core/DataModel/ITransientData.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "TChain.h"
#include "TFile.h"

#include <concepts>
#include <memory>

namespace MACE::Core {

using DataModel::IsTransientData;
using Utility::ObserverPtr;

class DataFactory final {
public:
    DataFactory() = default;
    ~DataFactory() = default;
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
    template<IsTransientData AData>
    TString GetTreeName(Long64_t treeIndex) const;

    /// Find a tree in a root file with name provided by AData and DataFactory settings.
    /// The tree is owned by the file.
    /// If not found, the return value is defined by ROOT (usually nullptr).
    template<IsTransientData AData>
    ObserverPtr<TTree> GetTree(TFile& file, Long64_t treeIndex = 0) const;
    /// Create a TChain of the list of ROOT files.
    template<IsTransientData AData, std::convertible_to<const char*> APath>
    std::shared_ptr<TChain> CreateChain(const std::vector<APath>& fileList, Long64_t treeIndex = 0) const;
    template<IsTransientData AData, typename APath> // clang-format off
        requires std::convertible_to<decltype(std::declval<APath>().c_str()), const char*>
    std::shared_ptr<TChain> CreateChain(const std::vector<APath>& fileList, Long64_t treeIndex = 0) const; // clang-format on
    /// Get the range of tree index in current tree name setting.
    template<IsTransientData AData>
    std::pair<Long64_t, Long64_t> GetTreeIndexRange(TFile& file) const;
    /// Create an empty tree with name provided by AData and DataFactory settings.
    /// The tree is owned by shared_ptr.
    template<IsTransientData AData>
    std::shared_ptr<TTree> CreateTree(Long64_t treeIndex = 0) const;
    /// Fill an existed tree with a data vector.
    /// The data type to be written in tree is specfied by ADataInTree. If not specfied, default to the
    /// type inside the incoming list (type pointed by ADataInListPointer).
    /// ADataInTree can be shrunken, which means just a part of column in the data vector will be written.
    ///   Note: this feature allows to fill the tree with less but exact columns that the data vector has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should make sure that ADataInTree represents exactly the same branches as the tree.
    template<IsTransientData ADataInTree, Concept::WeakPointerImitator ADataInListPointer> // clang-format off
        requires std::derived_from<typename std::pointer_traits<ADataInListPointer>::element_type, ADataInTree>
    static void FillTree(const std::vector<ADataInListPointer>& dataList, TTree& tree, bool connected = false); // clang-format on
    template<Concept::WeakPointerImitator ADataInListPointer>
    static void FillTree(const std::vector<ADataInListPointer>& dataList, TTree& tree, bool connected = false);
    /// Same effect as invoke CreateTree<ADataInTree>(treeIndex) and FillTree<ADataInTree>(dataList, tree, true).
    template<IsTransientData ADataInTree, Concept::WeakPointerImitator ADataInListPointer> // clang-format off
        requires std::derived_from<typename std::pointer_traits<ADataInListPointer>::element_type, ADataInTree>
    std::shared_ptr<TTree> CreateAndFillTree(const std::vector<ADataInListPointer>& dataList, Long64_t treeIndex = 0) const; // clang-format on
    template<Concept::WeakPointerImitator ADataInListPointer>
    std::shared_ptr<TTree> CreateAndFillTree(const std::vector<ADataInListPointer>& dataList, Long64_t treeIndex = 0) const;
    /// Create a data vector and fill it with a tree.
    /// Entries to be filled are determined by [entriesRange.first, entriesRange.second).
    /// The data type stores in the data vector is specfied by AData.
    /// AData can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which AData needs.
    /// It's user's responsibility to ensure the availability of entriesRange.
    template<IsTransientData AData>
    static std::vector<std::shared_ptr<AData>> CreateAndFillList(TTree& tree, const std::pair<Long64_t, Long64_t>& entriesRange, bool connected = false);
    /// Create a data vector and fill it with a tree.
    /// The data type stores in the data vector is specfied by AData.
    /// AData can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which AData needs.
    template<IsTransientData AData>
    static std::vector<std::shared_ptr<AData>> CreateAndFillList(TTree& tree, bool connected = false);
    /// Create a data vector and fill it with a tree. The tree is get via GetTree(TFile& file, Long64_t treeIndex).
    /// Entries to be filled are determined by [entriesRange.first, entriesRange.second).
    /// The data type stores in the data vector is specfied by AData.
    /// AData can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which AData needs.
    /// It's user's responsibility to ensure the availability of entriesRange.
    template<IsTransientData AData>
    std::vector<std::shared_ptr<AData>> CreateAndFillList(TFile& file, const std::pair<Long64_t, Long64_t>& entriesRange, Long64_t treeIndex = 0, bool connected = false) const;
    /// Create a data vector and fill it with a tree. The tree is get via GetTree(TFile& file, Long64_t treeIndex).
    /// The data type stores in the data vector is specfied by AData.
    /// AData can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which AData needs.
    template<IsTransientData AData>
    std::vector<std::shared_ptr<AData>> CreateAndFillList(TFile& file, Long64_t treeIndex = 0, bool connected = false) const;

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

#include "MACE/Core/DataFactory.inl"
