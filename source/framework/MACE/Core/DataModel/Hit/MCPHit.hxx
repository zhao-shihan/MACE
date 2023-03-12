#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Core/DataModel/TransientData.hxx"
#include "MACE/Utility/VectorAssign.hxx"
#include "MACE/stdx/array_alias.hxx"

#include <array>
#include <string_view>
#include <utility>

namespace MACE::Core::DataModel::Hit {

class MCPHit {
public:
    inline MCPHit() noexcept;
    virtual ~MCPHit() = default;

    MCPHit(const MCPHit&) noexcept = default;
    MCPHit(MCPHit&&) noexcept = default;
    MCPHit& operator=(const MCPHit&) noexcept = default;
    MCPHit& operator=(MCPHit&&) noexcept = default;

    const auto& HitTime() const { return fHitTime; }
    const auto& HitPosition() const { return fHitPosition; }
    template<Concept::NumericVector2D T>
    auto HitPosition() const { return Utility::VectorCast<T>(fHitPosition); }

    void HitTime(double val) { fHitTime = val; }
    void HitPosition(const stdx::array2d& x) { fHitPosition = x; }
    void HitPosition(auto&& x) { Utility::VectorAssign(fHitPosition, std::forward<decltype(x)>(x)); }

    inline void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return std::string_view("MCPHit"); }

private:
    double fHitTime;
    stdx::array2d fHitPosition;

    static BranchSocket::DoubleBranchSocket fgHitTime;
    static BranchSocket::Vector2FBranchSocket fgHitPosition;
};
static_assert(TransientData<MCPHit>);

} // namespace MACE::Core::DataModel::Hit

#include "MACE/Core/DataModel/Hit/MCPHit.inl"
