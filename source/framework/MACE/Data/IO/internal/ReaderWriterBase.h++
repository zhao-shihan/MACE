#pragma once

#include "MACE/Data/Model/DataModel.h++"
#include "MACE/Data/Model/NamedField.h++"
#include "MACE/Extension/gslx/index_sequence.h++"
#include "MACE/Extension/stdx/tuple_like.h++"
#include "MACE/Utility/FixedString.h++"

#include "TBranch.h"
#include "TTree.h"

#include "gsl/gsl"

#include "fmt/format.h"

#include <algorithm>
#include <array>
#include <cinttypes>
#include <concepts>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace MACE::Data::inline IO::internal {

namespace internal {

// template<typename T>
// struct BranchPointer;

// template<Concept::ROOTFundamental T>
// struct BranchPointer<T> {
//     using TypeForCreate = T*;
//     using TypeForSetAddress = T*;
// };

// template<Concept::ROOTFundamental T, std::size_t N>
// struct BranchPointer<std::array<T, N>> {
//     using TypeForCreate = std::array<T, N>*;
//     using TypeForSetAddress = T*;
// };

// template<std::size_t N>
// struct BranchPointer<FixedString<N>> {
//     using TypeForCreate = gsl::zstring;
//     using TypeForSetAddress = gsl::zstring;
// };

// template<typename T>
//     requires std::is_class_v<T>
// struct BranchPointer<T> {
//     using TypeForCreate = T*;
//     using TypeForSetAddress = T**;
// };

template<typename T>
struct IsStdArray
    : std::false_type {};

template<typename T, std::size_t N>
struct IsStdArray<std::array<T, N>>
    : std::true_type {};

template<typename T>
struct IsFixedString
    : std::false_type {};

template<std::size_t N>
struct IsFixedString<FixedString<N>>
    : std::true_type {};

} // namespace internal

template<DataModel AModel, std::derived_from<TTree> ATree>
class ReaderWriterBase {
public:
    using ValueType = typename AModel::Entry;
    using SizeType = decltype(std::declval<TTree>().GetEntries());
    using DifferenceType = std::make_signed_t<SizeType>;

    using value_type = ValueType;
    using size_type = SizeType;
    using difference_type = DifferenceType;

protected:
    template<gsl::index I>
    using Field = typename AModel::template Field<I>;
    template<gsl::index I>
    using FieldType = typename Field<I>::Type;

protected:
    ReaderWriterBase(ATree& tree);
    ~ReaderWriterBase();

public:
    auto Tree() const -> auto& { return fEssential->tree; }

protected:
    auto Entry() const -> auto& { return fEssential->entry; }
    template<gsl::index I>
    auto FieldPointer() const -> decltype(auto) { return std::get<I>(fFieldPointerList); }

protected:
    struct Essential {
        ATree& tree;
        ValueType entry;
    };

protected:
    std::shared_ptr<Essential> fEssential;

private:
    std::vector<void*> fClassPointerStorage;
    const std::array<void*, AModel::NField()> fFieldPointerList;
};

} // namespace MACE::Data::inline IO::internal

#include "MACE/Data/IO/internal/ReaderWriterBase.inl"
