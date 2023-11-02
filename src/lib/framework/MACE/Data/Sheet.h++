#pragma once

#include "MACE/Data/CEvalNTSTA.h++"
#include "MACE/Data/Entry.h++"
#include "MACE/Data/Model.h++"
#include "MACE/Data/internal/BranchAddressHelper.h++"
#include "MACE/Extension/stdx/to_signed.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "TBranch.h"
#include "TChain.h"

#include "gsl/gsl"

#include "fmt/format.h"

#include <algorithm>
#include <array>
#include <cinttypes>
#include <compare>
#include <concepts>
#include <initializer_list>
#include <memory>
#include <ranges>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace MACE::Data {

template<Modelizable... Ts>
class Sheet final {
private:
    class DataSource;

    class Row final {
    public:
        Row(gsl::index index, const DataSource& data);

        auto Get() const;
        template<CEvalNTSTA... ANames>
        auto Get() const { return Get<Model<Ts...>::template Index<ANames>()...>(); }
        template<gsl::index... Is>
        auto Get() const;

        auto operator==(const Row& that) const { return fIndex == that.fIndex; }
        auto operator<=>(const Row& that) const { return fIndex <=> that.fIndex; }

    private:
        gsl::index fIndex;
        const DataSource* fData;
    };

    using RowArray = std::vector<Row>;

public:
    using iterator = typename RowArray::iterator;
    using const_iterator = typename RowArray::const_iterator;
    using reverse_iterator = typename RowArray::reverse_iterator;
    using const_reverse_iterator = typename RowArray::const_reverse_iterator;

public:
    Sheet(const std::string& name, const std::string& file);
    Sheet(const std::string& name, std::initializer_list<std::string> files);
    template<std::ranges::input_range R>
        requires std::same_as<std::decay_t<std::ranges::range_value_t<R>>, std::string>
    Sheet(const std::string& name, const R& files);

    // ExecuteWithOnlyEnabling
    // ExecuteWithOnlyDisabling

    auto operator[](gsl::index i) const -> const auto& { return fRow[i]; }
    template<CEvalNTSTA... ANames>
    auto At(gsl::index i) const { return fRow[i].template Get<ANames...>(); }
    template<gsl::index... Is>
    auto At(gsl::index i) const { return fRow[i].template Get<Is...>(); }

    auto begin() noexcept { return fRow.begin(); }
    auto begin() const noexcept { return fRow.begin(); }
    auto cbegin() const noexcept { return fRow.cbegin(); }
    auto end() noexcept { return fRow.end(); }
    auto end() const noexcept { return fRow.end(); }
    auto cend() const noexcept { return fRow.cend(); }
    auto rbegin() noexcept { return fRow.rbegin(); }
    auto rbegin() const noexcept { return fRow.rbegin(); }
    auto crbegin() const noexcept { return fRow.crbegin(); }
    auto rend() noexcept { return fRow.rend(); }
    auto rend() const noexcept { return fRow.rend(); }
    auto crend() const noexcept { return fRow.crend(); }

private:
    class DataSource final {
    public:
        DataSource(const std::string& name, std::initializer_list<std::string> files);
        template<std::ranges::input_range R>
            requires std::same_as<std::decay_t<std::ranges::range_value_t<R>>, std::string>
        DataSource(const std::string& name, const R& files);

        auto ChainEntries() const { return fChainEntries; }
        auto ExtensionSize() const { return fExtension.size(); }
        auto Size() const { return ChainEntries() + ExtensionSize(); }
        auto Fetch(gsl::index i) const;

        auto Status() const -> const auto& { return fStatus; }
        template<CEvalNTSTA... ANames>
        auto Enable() const -> void { Enable<Model<Ts...>::template Index<ANames>()...>(); }
        template<gsl::index... Is>
        auto Enable() const -> void;
        template<CEvalNTSTA... ANames>
        auto Disable() const -> void { Disable<Model<Ts...>::template Index<ANames>()...>(); }
        template<gsl::index... Is>
        auto Disable() const -> void;
        auto EnableAll() const -> void;

    private:
        auto SetAllBranchAddress() const -> void;

    private:
        std::unique_ptr<TChain> fChain;
        std::size_t fChainEntries;
        mutable Entry<Model<Ts...>> fEntry4Chain;
        mutable internal::BranchAddressHelper<Entry<Model<Ts...>>> fBranchAddressHelper;

        std::unordered_map<gsl::index, Entry<Model<Ts...>>> fExtension;

        mutable std::array<bool, Model<Ts...>::NField()> fStatus;

        mutable gsl::index fFetchedIndex;
        mutable const Entry<Model<Ts...>>* fFetchedEntry;
    };

private:
    RowArray fRow;
    DataSource fData;
};

} // namespace MACE::Data

#include "MACE/Data/Sheet.inl"
