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

template<class AData>
concept IsTransientData =
    std::derived_from<AData, ITransientData> and
    std::semiregular<AData> and
    std::movable<AData> and
    std::is_nothrow_constructible_v<AData> and
    std::is_nothrow_copy_constructible_v<AData> and
    std::is_nothrow_move_constructible_v<AData> and
    std::is_nothrow_copy_assignable_v<AData> and
    std::is_nothrow_move_assignable_v<AData> and
    requires(const AData data, TTree tree) {
    { AData::CreateBranches(tree) } -> std::same_as<void>;
    { AData::ConnectToBranches(tree) } -> std::same_as<void>;
    { data.FillBranchSockets() }
    noexcept->std::same_as<void>;
    { AData::BasicTreeName() }
    noexcept->std::same_as<const char*>;
};

} // namespace MACE::Core::DataModel
