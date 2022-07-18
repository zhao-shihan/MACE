#pragma once

#include <concepts>

class TTree;

namespace MACE::Core::DataModel {

class ITransientData {
public:
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

    // Override this in derived classes at least once!
    static consteval const char* BasicTreeName() noexcept { return "__Base__"; }
    // Extend (override & invoke) this in derived classes!
    static void CreateBranches(TTree&) {}
    // Extend (override & invoke) this in derived classes!
    static void ConnectToBranches(TTree&) {}
    // Extend (override & invoke) this in derived classes!
    void FillBranchSockets() const noexcept {}
};

template<class DataT>
concept IsTransientData =
    std::derived_from<DataT, ITransientData> and
    std::semiregular<DataT> and
    std::movable<DataT> and
    std::is_nothrow_constructible_v<DataT> and
    std::is_nothrow_copy_constructible_v<DataT> and
    std::is_nothrow_move_constructible_v<DataT> and
    std::is_nothrow_copy_assignable_v<DataT> and
    std::is_nothrow_move_assignable_v<DataT> and
    requires(const DataT data, TTree tree) {
    { DataT::CreateBranches(tree) } -> std::same_as<void>;
    { DataT::ConnectToBranches(tree) } -> std::same_as<void>;
    { data.FillBranchSockets() }
    noexcept->std::same_as<void>;
    { DataT::BasicTreeName() }
    noexcept->std::same_as<const char*>;
};

} // namespace MACE::Core::DataModel
