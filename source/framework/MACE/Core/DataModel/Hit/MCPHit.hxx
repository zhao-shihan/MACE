#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/TransientData.hxx"
#include "MACE/Utility/AssignVector.hxx"

#include <string_view>
#include <utility>

namespace MACE::Core::DataModel::Hit {

using namespace std::string_view_literals;

class MCPHit {
public:
    MCPHit() noexcept;
    virtual ~MCPHit() = default;

    MCPHit(const MCPHit&) noexcept = default;
    MCPHit(MCPHit&&) noexcept = default;
    MCPHit& operator=(const MCPHit&) noexcept = default;
    MCPHit& operator=(MCPHit&&) noexcept = default;

    const auto& HitTime() const { return fHitTime; }
    const auto& GetHitPosition() const { return fHitPosition; }
    const auto& GetHitPositionVariance() const { return fHitPositionVariance; }

    void HitTime(double val) { fHitTime = val; }
    void SetHitPosition(auto&&... x)
        requires(sizeof...(x) > 0)
    { Utility::AssignVector2D(fHitPosition, std::forward<decltype(x)>(x)...); }
    void SetHitPositionVariance(auto&&... s)
        requires(sizeof...(s) > 0)
    { Utility::AssignVector2D(fHitPositionVariance, std::forward<decltype(s)>(s)...); }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "MCPHit"sv; }

private:
    double fHitTime;
    Eigen::Vector2d fHitPosition;
    Eigen::Vector2d fHitPositionVariance;

    static BranchSocket::DoubleBranchSocket fgHitTime;
    static BranchSocket::Vector2FBranchSocket fgHitPosition;
    static BranchSocket::Vector2FBranchSocket fgHitPositionVariance;
};
static_assert(TransientData<MCPHit>);

} // namespace MACE::Core::DataModel::Hit
