#pragma once

#include "MACE/Data/IO/internal/ReaderWriterBase.h++"
#include "MACE/Data/Model/DataModel.h++"
#include "MACE/Extension/gslx/index_sequence.h++"
#include "MACE/Utility/FixedString.h++"

#include "TTree.h"

#include "gsl/gsl"

#include <array>
#include <compare>
#include <concepts>
#include <limits>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <utility>

namespace MACE::Data::inline IO {

template<DataModel AModel, std::derived_from<TTree> ATree>
class Reader final : public internal::ReaderWriterBase<AModel, ATree> {
private:
    using Base = internal::ReaderWriterBase<AModel, ATree>;
    using ValueType = typename Base::ValueType;
    using SizeType = typename Base::SizeType;
    using DifferenceType = typename Base::DifferenceType;
    template<gsl::index I>
    using Field = typename Base::template Field<I>;

public:
    class ConstIterator final {
        friend class Reader;

    private:
        ConstIterator(std::shared_ptr<const typename Base::Essential> essential, gsl::index index);

    public:
        ConstIterator() = default;

        auto operator*() const { return (this->Tree().GetEntry(fIndex), this->Entry()); }
        auto operator->() const { return std::make_unique<ValueType>(**this); }

        auto operator++() { return (++fIndex, *this); }
        auto operator++(int) -> ConstIterator { return {fEssential, fIndex++}; }
        auto operator--() { return (--fIndex, *this); }
        auto operator--(int) -> ConstIterator { return {fEssential, fIndex--}; }

        auto operator-(const ConstIterator& that) const -> DifferenceType;

        auto operator+=(DifferenceType n) { return (fIndex += n, *this); }
        auto operator+(DifferenceType n) const { return ConstIterator(*this) += n; }
        friend auto operator+(DifferenceType n, ConstIterator i) { return i += n; }
        auto operator-=(DifferenceType n) { return (fIndex -= n, *this); }
        auto operator-(DifferenceType n) const { return ConstIterator(*this) -= n; }

        auto operator[](gsl::index i) const { return *(*this + i); }

        auto operator==(const ConstIterator& that) const -> bool;
        auto operator<=>(const ConstIterator& that) const -> std::strong_ordering;

    private:
        auto TreeAddress() const -> const TTree* { return std::addressof(fEssential->tree); }

    private:
        const std::shared_ptr<const typename Base::Essential> fEssential;
        gsl::index fIndex;
    };

    using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

public:
    Reader(ATree& tree);

    auto SignedSize() const -> std::make_signed_t<SizeType> { return this->Tree().GetEntries(); }
    auto Size() const -> SizeType { return SignedSize(); }

    auto Begin() const -> ConstIterator { return {this->fEssential, 0}; }
    auto End() const -> ConstIterator { return {this->fEssential, SignedSize()}; }
    auto ReverseBegin() const { return ConstReverseIterator(End()); }
    auto ReverseEnd() const { return ConstReverseIterator(Begin()); }

    auto operator[](gsl::index i) const { return (this->Tree().GetEntry(i), this->Entry()); }

public:
    using const_iterator = ConstIterator;
    using const_reverse_iterator = ConstReverseIterator;

public:
    auto ssize() const { return SignedSize(); }
    auto size() const { return Size(); }

    auto begin() const { return Begin(); }
    auto end() const { return End(); }
    auto rbegin() const { return ReverseBegin(); }
    auto rend() const { return ReverseEnd(); }
};

} // namespace MACE::Data::inline IO

#include "MACE/Data/IO/Reader.inl"
