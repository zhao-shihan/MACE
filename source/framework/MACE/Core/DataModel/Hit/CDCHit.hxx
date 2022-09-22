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

class CDCHit {
public:
    CDCHit() noexcept;
    virtual ~CDCHit() = default;

    CDCHit(const CDCHit&) noexcept = default;
    CDCHit(CDCHit&&) noexcept = default;
    CDCHit& operator=(const CDCHit&) noexcept = default;
    CDCHit& operator=(CDCHit&&) noexcept = default;

    const auto& HitTime() const { return fHitTime; }
    const auto& DriftDistance() const { return fDriftDistance; }
    const auto& HitPositionZ() const { return fHitPositionZ; }
    const auto& DriftDistanceVariance() const { return fDriftDistanceVariance; }
    const auto& HitPositionZVariance() const { return fHitPositionZVariance; }
    const auto& WirePosition() const { return fWirePosition; }
    const auto& WireDirection() const { return fWireDirection; }
    const auto& CellID() const { return fCellID; }
    const auto& LayerID() const { return fLayerID; }

    void HitTime(double val) { fHitTime = val; }
    void DriftDistance(double d) { fDriftDistance = d; }
    void HitPositionZ(double z) { fHitPositionZ = z; }
    void DriftDistanceVariance(double val) { fDriftDistanceVariance = val; }
    void HitPositionZVariance(double val) { fHitPositionZVariance = val; }
    void WirePosition(auto&&... x) requires(sizeof...(x) > 0) { Utility::AssignVector2D(fWirePosition, std::forward<decltype(x)>(x)...); }
    void WireDirection(auto&&... t) requires(sizeof...(t) > 0) { Utility::AssignVector3D(fWireDirection, std::forward<decltype(t)>(t)...); }
    void CellID(int val) { fCellID = val; }
    void LayerID(int val) { fLayerID = val; }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "CDCHit"sv; }

private:
    double fHitTime;
    double fDriftDistance;
    double fHitPositionZ;
    double fDriftDistanceVariance;
    double fHitPositionZVariance;
    Eigen::Vector2d fWirePosition;
    Eigen::Vector3d fWireDirection;
    int fCellID;
    int fLayerID;

    static BranchSocket::DoubleBranchSocket fgHitTime;
    static BranchSocket::FloatBranchSocket fgDriftDistance;
    static BranchSocket::FloatBranchSocket fgHitPositionZ;
    static BranchSocket::FloatBranchSocket fgDriftDistanceVariance;
    static BranchSocket::FloatBranchSocket fgHitPositionZVariance;
    static BranchSocket::Vector2FBranchSocket fgWirePosition;
    static BranchSocket::Vector3FBranchSocket fgWireDirection;
    static BranchSocket::IntBranchSocket fgCellID;
    static BranchSocket::IntBranchSocket fgLayerID;
};
static_assert(TransientData<CDCHit>);

} // namespace MACE::Core::DataModel::Hit
