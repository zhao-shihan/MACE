#pragma once

#include "MACE/Data/IO/internal/ReaderWriterBase.h++"
#include "MACE/Data/Model/Modelized.h++"
#include "MACE/Extension/gslx/index_sequence.h++"

#include "TTree.h"

#include "gsl/gsl"

#include <algorithm>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace MACE::Data::inline IO {

template<Modelized AModel>
class Reader final : public internal::ReaderWriterBase<AModel> {
private:
    using Base = internal::ReaderWriterBase<AModel>;
    using ValueType = typename Base::ValueType;
    using SizeType = typename Base::SizeType;
    using DifferenceType = typename Base::DifferenceType;
    template<gsl::index I>
    using Field = typename Base::template Field<I>;
    using Essential = typename Base::Essential;

public:
    class ConstIterator final {
    public:
        using ValueType = typename Reader::ValueType;
        using value_type = ValueType;

    public:
        ConstIterator() = default;
        ConstIterator(const Essential& essential, gsl::index index);

    private:
        ConstIterator(const Essential* essential, gsl::index index);

    public:
        auto operator*() const { return (fEssential->tree.GetEntry(fIndex), fEssential->entry); }
        auto operator->() const { return std::make_unique<ValueType>(**this); }

        auto operator++() -> auto& { return (++fIndex, *this); }
        auto operator++(int) -> ConstIterator { return {fEssential, fIndex++}; }
        auto operator--() -> auto& { return (--fIndex, *this); }
        auto operator--(int) -> ConstIterator { return {fEssential, fIndex--}; }

        auto operator-(const ConstIterator& that) const -> DifferenceType;

        auto operator+=(DifferenceType n) -> auto& { return (fIndex += n, *this); }
        auto operator+(DifferenceType n) const { return ConstIterator{*this} += n; }
        friend auto operator+(DifferenceType n, ConstIterator i) { return i += n; }
        auto operator-=(DifferenceType n) -> auto& { return (fIndex -= n, *this); }
        auto operator-(DifferenceType n) const { return ConstIterator{*this} -= n; }

        auto operator[](gsl::index i) const { return *(*this + i); }

        auto operator==(const ConstIterator& that) const { return TreeAddress() == that.TreeAddress() and fIndex == that.fIndex; }
        auto operator<=>(const ConstIterator& that) const { return std::tuple{TreeAddress(), fIndex} <=> std::tuple{that.TreeAddress(), that.fIndex}; }

    private:
        auto TreeAddress() const -> const TTree* { return &fEssential->tree; }

    private:
        const Essential* fEssential;
        gsl::index fIndex;
    };

    using Iterator = ConstIterator;
    using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
    using ReverseIterator = ConstReverseIterator;

public:
    explicit Reader(TTree& tree);

    auto Size() const -> SizeType { return this->Tree().GetEntries(); }
    auto Begin() const -> Iterator { return {this->fEssential, 0}; }
    auto End() const -> Iterator { return {this->fEssential, Size()}; }
    auto ReverseBegin() const { return ReverseIterator{End()}; }
    auto ReverseEnd() const { return ReverseIterator{Begin()}; }

    auto operator[](gsl::index i) const { return (this->Tree().GetEntry(i), this->Entry()); }

    template<template<typename, typename...> typename ASequenceContainer = std::vector>
    auto IteratorCollection() const -> ASequenceContainer<Iterator>;

public:
    using iterator = Iterator;
    using const_iterator = ConstIterator;
    using reverse_iterator = ReverseIterator;
    using const_reverse_iterator = ConstReverseIterator;

public:
    auto size() const { return Size(); }
    auto begin() const { return Begin(); }
    auto end() const { return End(); }
    auto rbegin() const { return ReverseBegin(); }
    auto rend() const { return ReverseEnd(); }
};

} // namespace MACE::Data::inline IO

#include "MACE/Data/IO/Reader.inl"
