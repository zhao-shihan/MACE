#pragma once

#include "MACE/Compatibility/std2b/ranges_iota.h++"
#include "MACE/Data/IO/internal/ReaderWriterBase.h++"
#include "MACE/Data/Model/Modelized.h++"
#include "MACE/Extension/gslx/index_sequence.h++"

#include "TTree.h"

#include "gsl/gsl"

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
    class Iterator final {
    public:
        using ValueType = typename Reader::ValueType;
        using value_type = ValueType;

    public:
        Iterator() = default;
        Iterator(gsl::index index, const Essential& essential);

    private:
        Iterator(gsl::index index, const Essential* essential);

    public:
        auto Index() const { return fIndex; }
        auto Tree() const -> auto& { return fEssential->tree; }

        auto operator*() const { return (fEssential->tree.GetEntry(fIndex), fEssential->entry); }
        auto operator->() const { return std::make_unique<ValueType>(**this); }

        auto operator++() -> auto& { return (++fIndex, *this); }
        auto operator++(int) -> Iterator { return {fIndex++, fEssential}; }
        auto operator--() -> auto& { return (--fIndex, *this); }
        auto operator--(int) -> Iterator { return {fIndex--, fEssential}; }

        auto operator-(const Iterator& that) const -> DifferenceType;

        auto operator+=(DifferenceType n) -> auto& { return (fIndex += n, *this); }
        auto operator+(DifferenceType n) const { return Iterator{*this} += n; }
        friend auto operator+(DifferenceType n, Iterator i) { return i += n; }
        auto operator-=(DifferenceType n) -> auto& { return (fIndex -= n, *this); }
        auto operator-(DifferenceType n) const { return Iterator{*this} -= n; }

        auto operator[](gsl::index i) const { return *(*this + i); }

        auto operator==(const Iterator& that) const { return fIndex == that.fIndex and &Tree() == &that.Tree(); }
        auto operator<=>(const Iterator& that) const { return std::tuple{fIndex, &Tree()} <=> std::tuple{that.fIndex, &that.Tree()}; }

    private:
        gsl::index fIndex;
        const Essential* fEssential;
    };

    using ConstIterator = Iterator;
    using ReverseIterator = std::reverse_iterator<Iterator>;
    using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

public:
    explicit Reader(TTree& tree);

    auto Size() const -> SizeType { return this->Tree().GetEntries(); }
    auto Begin() const -> Iterator { return {0, this->fEssential}; }
    auto End() const -> Iterator { return {Size(), this->fEssential}; }
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

template<Modelized AModel>
using ReadIterator = typename Reader<AModel>::Iterator;

} // namespace MACE::Data::inline IO

#include "MACE/Data/IO/Reader.inl"
