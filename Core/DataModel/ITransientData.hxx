#pragma once

#include "TTree.h"

#include <concepts>

namespace MACE::Core::DataModel {

class ITransientData {
protected:
    ITransientData() noexcept = default;
    ITransientData(const ITransientData& data) noexcept = default;
    ITransientData(ITransientData&& data) noexcept = default;
    virtual ~ITransientData() noexcept = 0;
    ITransientData& operator=(const ITransientData& data) noexcept = default;
    ITransientData& operator=(ITransientData&& data) noexcept = default;

    bool operator==(const ITransientData&) = delete;
    bool operator!=(const ITransientData&) = delete;
    bool operator<(const ITransientData&) = delete;
    bool operator<=(const ITransientData&) = delete;
    bool operator>(const ITransientData&) = delete;
    bool operator>=(const ITransientData&) = delete;
    auto operator<=>(const ITransientData&) = delete;

    // Extend (override & invoke) this in derived classes!
    static void CreateBranches(TTree&) {}
    // Extend (override & invoke) this in derived classes!
    static void ConnectToBranches(TTree&) {}
    // Extend (override & invoke) this in derived classes!
    void FillBranchSockets() const noexcept {}

private:
    // Override this in derived classes at least once!
    static consteval const char* BasicTreeName() noexcept { return "__Base__"; }
};

template<class Data_t>
concept IsTransientData =
    std::derived_from<Data_t, ITransientData> and
    std::semiregular<Data_t> and
    std::movable<Data_t> and
    std::is_nothrow_constructible_v<Data_t> and
    std::is_nothrow_copy_constructible_v<Data_t> and
    std::is_nothrow_move_constructible_v<Data_t> and
    std::is_nothrow_copy_assignable_v<Data_t> and
    std::is_nothrow_move_assignable_v<Data_t> and
    requires(const Data_t data, TTree tree) {
    { Data_t::CreateBranches(tree) } -> std::same_as<void>;
    { Data_t::ConnectToBranches(tree) } -> std::same_as<void>;
    { data.FillBranchSockets() }
    noexcept->std::same_as<void>;
    { Data_t::BasicName() }
    noexcept->std::same_as<const char*>;
};

} // namespace MACE::Core::DataModel
