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
    using value_type = typename Base::value_type;
    using size_type = typename Base::size_type;
    using difference_type = typename Base::difference_type;
    template<gsl::index I>
    using Field = typename Base::template Field<I>;

public:
    class const_iterator final {
        friend class Reader;

    private:
        const_iterator(const Reader* reader, gsl::index index);

    public:
        const_iterator() = default;

        auto operator*() const { return (*fReader)[fIndex]; }
        auto operator->() const { return; }

        auto operator++() { return (++fIndex, *this); }
        auto operator++(int) -> const_iterator { return {fReader, fIndex++}; }
        auto operator--() { return (--fIndex, *this); }
        auto operator--(int) -> const_iterator { return {fReader, fIndex--}; }

        auto operator-(const const_iterator& that) const -> difference_type;

        auto operator+=(difference_type n) { return (fIndex += n, *this); }
        auto operator+(difference_type n) const { return const_iterator(*this) += n; }
        friend auto operator+(difference_type n, const_iterator i) { return i += n; }
        auto operator-=(difference_type n) { return (fIndex -= n, *this); }
        auto operator-(difference_type n) const { return const_iterator(*this) -= n; }

        auto operator[](difference_type n) const { return (*fReader)[fIndex + n]; }

        auto operator==(const const_iterator& that) const -> bool;
        auto operator<=>(const const_iterator& that) const -> std::strong_ordering;

    private:
        auto TreeAddress() const -> const TTree* { return &fReader->Tree(); }

    private:
        const Reader* const fReader;
        gsl::index fIndex;
    };

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
    Reader(ATree& tree);

    auto size() const -> size_type { return this->fTree.GetEntries(); }
    auto ssize() const -> std::make_signed_t<size_type> { return size(); }

    auto begin() const -> const_iterator { return {this, 0}; }
    auto end() const -> const_iterator { return {this, size()}; }
    auto cbegin() const -> { return begin(); }
    auto cend() const -> { return end(); }
    auto rbegin() const { return const_reverse_iterator(end()); }
    auto rend() const { return const_reverse_iterator(begin()); }
    auto crbegin() const -> { return rbegin(); }
    auto crend() const -> { return rend(); }

    auto operator[](gsl::index i) const { return (this->fTree.GetEntry(i), *this->fEntry); }
};

} // namespace MACE::Data::inline IO

#include "MACE/Data/IO/Reader.inl"
