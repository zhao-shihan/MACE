#pragma once

#include "MACE/Concept/PointerImitator.h++"
#include "MACE/DataModel/TransientData.h++"
#include "MACE/Utility/MerelyMoveableBase.h++"

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"

#include "gsl/gsl"

#include <concepts>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

namespace MACE::DataModel {

class [[deprecated]] DataFactory final : public MerelyMoveableBase {
public:
    DataFactory();

    void TreeNamePrefixFormat(std::string_view prefix);
    void TreeNameSuffixFormat(std::string_view suffix);

    const auto& TreeNamePrefixFormat() const { return fPrefixFormat; }
    const auto& TreeNameSuffixFormat() const { return fSuffixFormat; }
    auto TreeNamePrefix(Long64_t i) const { return fPrefixHasIndex ? (fPrefix.first + std::to_string(i) + fPrefix.second) : fPrefix.first; }
    auto TreeNameSuffix(Long64_t i) const { return fSuffixHasIndex ? (fSuffix.first + std::to_string(i) + fSuffix.second) : fSuffix.first; }
    template<TransientData AData>
    auto TreeName(Long64_t treeIndex) const { return TreeNamePrefix(treeIndex) + std::string(AData::BasicTreeName()) + TreeNameSuffix(treeIndex); }

    /// Find a tree in a root file with name provided by AData and DataFactory settings.
    /// The tree is owned by the file.
    /// If not found, the return value is defined by ROOT (usually nullptr).
    template<TransientData AData>
    TTree* FindTree(TFile& file, Long64_t treeIndex = -1) const { return file.Get<TTree>(TreeName<AData>(treeIndex).c_str()); }
    /// Create a TChain of the list of ROOT files.
    template<TransientData AData, std::convertible_to<gsl::czstring> APath>
    std::shared_ptr<TChain> CreateChain(const std::vector<APath>& fileList, Long64_t treeIndex = -1) const;
    template<TransientData AData, typename APath>
        requires std::convertible_to<decltype(std::declval<APath>().c_str()), gsl::czstring>
    std::shared_ptr<TChain> CreateChain(const std::vector<APath>& fileList, Long64_t treeIndex = -1) const;
    /// Get the range of tree index in current tree name setting.
    template<TransientData AData>
    std::pair<Long64_t, Long64_t> GetTreeIndexRange(TFile& file) const;
    /// Create an empty tree with name provided by AData and DataFactory settings.
    /// The tree is owned by shared_ptr.
    template<TransientData AData>
    std::shared_ptr<TTree> CreateTree(Long64_t treeIndex = -1) const;
    /// Fill an existed tree with a data vector.
    /// The data type to be written in tree is specfied by ADataInTree. If not specfied, default to the
    /// type inside the incoming list (type pointed by ADataInListPointer).
    /// ADataInTree can be shrunken, which means just a part of column in the data vector will be written.
    ///   Note: this feature allows to fill the tree with less but exact columns that the data vector has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should make sure that ADataInTree represents exactly the same branches as the tree.
    template<TransientData ADataInTree, Concept::WeakPointerImitator ADataInListPointer>
        requires std::derived_from<typename std::pointer_traits<ADataInListPointer>::element_type, ADataInTree>
    static void FillTree(const std::vector<ADataInListPointer>& dataList, TTree& tree, bool connected = false);
    template<Concept::WeakPointerImitator ADataInListPointer>
    static void FillTree(const std::vector<ADataInListPointer>& dataList, TTree& tree, bool connected = false);
    /// Same effect as invoke CreateTree<ADataInTree>(treeIndex) and FillTree<ADataInTree>(dataList, tree, true).
    template<TransientData ADataInTree, Concept::WeakPointerImitator ADataInListPointer>
        requires std::derived_from<typename std::pointer_traits<ADataInListPointer>::element_type, ADataInTree>
    std::shared_ptr<TTree> CreateAndFillTree(const std::vector<ADataInListPointer>& dataList, Long64_t treeIndex = -1) const;
    template<Concept::WeakPointerImitator ADataInListPointer>
    std::shared_ptr<TTree> CreateAndFillTree(const std::vector<ADataInListPointer>& dataList, Long64_t treeIndex = -1) const;
    /// Create a data vector and fill it with a tree.
    /// Entries to be filled are determined by [entriesRange.first, entriesRange.second).
    /// The data type stores in the data vector is specfied by AData.
    /// AData can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which AData needs.
    /// It's user's responsibility to ensure the availability of entriesRange.
    template<TransientData AData>
    static std::vector<std::shared_ptr<AData>> CreateAndFillList(TTree& tree, const std::pair<Long64_t, Long64_t>& entriesRange, bool connected = false);
    /// Create a data vector and fill it with a tree.
    /// The data type stores in the data vector is specfied by AData.
    /// AData can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which AData needs.
    template<TransientData AData>
    static std::vector<std::shared_ptr<AData>> CreateAndFillList(TTree& tree, bool connected = false);
    /// Create a data vector and fill it with a tree. The tree is get via FindTree(TFile& file, Long64_t treeIndex).
    /// Entries to be filled are determined by [entriesRange.first, entriesRange.second).
    /// The data type stores in the data vector is specfied by AData.
    /// AData can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which AData needs.
    /// It's user's responsibility to ensure the availability of entriesRange.
    template<TransientData AData>
    std::vector<std::shared_ptr<AData>> CreateAndFillList(TFile& file, const std::pair<Long64_t, Long64_t>& entriesRange, Long64_t treeIndex = -1, bool connected = false) const;
    /// Create a data vector and fill it with a tree. The tree is get via FindTree(TFile& file, Long64_t treeIndex).
    /// The data type stores in the data vector is specfied by AData.
    /// AData can be shrunken, which means just a part of branch in the tree will be read.
    ///   Note: this feature allows to create a data vector with less but exact columns that the tree has.
    /// Note: there is no static branch infomation for the tree, so
    /// user should ensure that the tree contains branches which AData needs.
    template<TransientData AData>
    std::vector<std::shared_ptr<AData>> CreateAndFillList(TFile& file, Long64_t treeIndex = -1, bool connected = false) const;

private:
    static std::pair<bool, std::pair<std::string, std::string>> SplitPrefixOrSuffixFormat(std::string_view format);

private:
    bool fPrefixHasIndex;
    bool fSuffixHasIndex;
    std::pair<std::string, std::string> fPrefix;
    std::pair<std::string, std::string> fSuffix;
    std::string fPrefixFormat;
    std::string fSuffixFormat;

    static constexpr std::string_view fgIndexer = "{}";
};

} // namespace MACE::DataModel

#include "MACE/DataModel/DataFactory.inl"
