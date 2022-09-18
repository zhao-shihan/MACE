#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/ITransientData.hxx"

namespace MACE::Core::DataModel::Hit {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::FloatBranchSocket;
using BranchSocket::IntBranchSocket;
using BranchSocket::Vector2FBranchSocket;
using BranchSocket::Vector3FBranchSocket;

class CDCHit : public ITransientData {
    using Base = ITransientData;

public:
    CDCHit() noexcept;
    CDCHit(const CDCHit& hit) noexcept = default;
    CDCHit(CDCHit&& hit) noexcept = default;
    virtual ~CDCHit() noexcept = default;
    CDCHit& operator=(const CDCHit& hit) noexcept = default;
    CDCHit& operator=(CDCHit&& hit) noexcept = default;

    const auto& HitTime() const { return fHitTime; }
    const auto& DriftDistance() const { return fDriftDistance; }
    const auto& HitPositionZ() const { return fHitPositionZ; }
    const auto& DriftDistanceVariance() const { return fDriftDistanceVariance; }
    const auto& HitPositionZVariance() const { return fHitPositionZVariance; }
    const auto& WirePosition() const { return fWirePosition; }
    const auto& WireDirection() const { return fWireDirection; }
    const auto& CellID() const { return fCellID; }
    const auto& LayerID() const { return fLayerID; }

    void HitTime(Double_t val) { fHitTime = val; }
    void DriftDistance(Double_t d) { fDriftDistance = d; }
    void HitPositionZ(Double_t z) { fHitPositionZ = z; }
    void DriftDistanceVariance(Double_t val) { fDriftDistanceVariance = val; }
    void HitPositionZVariance(Double_t val) { fHitPositionZVariance = val; }
    void WirePosition(auto&& pos) { fWirePosition = std::forward<decltype(pos)>(pos); }
    void WirePosition(Double_t x, Double_t y) { fWirePosition = {x, y}; }
    void SetWireDirection(auto&& dir) { fWireDirection = std::forward<decltype(dir)>(dir); }
    void SetWireDirection(Double_t tx, Double_t ty, Double_t tz) { fWireDirection = {tx, ty, tz}; }
    void SetCellID(Int_t val) { fCellID = val; }
    void SetLayerID(Int_t val) { fLayerID = val; }

    static consteval const char* BasicTreeName() noexcept { return "CDCHit"; }
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    Double_t fHitTime;
    Double_t fDriftDistance;
    Double_t fHitPositionZ;
    Double_t fDriftDistanceVariance;
    Double_t fHitPositionZVariance;
    Eigen::Vector2d fWirePosition;
    Eigen::Vector3d fWireDirection;
    Int_t fCellID;
    Int_t fLayerID;

    static DoubleBranchSocket fgHitTime;
    static FloatBranchSocket fgDriftDistance;
    static FloatBranchSocket fgHitPositionZ;
    static FloatBranchSocket fgDriftDistanceVariance;
    static FloatBranchSocket fgHitPositionZVariance;
    static Vector2FBranchSocket fgWirePosition;
    static Vector3FBranchSocket fgWireDirection;
    static IntBranchSocket fgCellID;
    static IntBranchSocket fgLayerID;
};

} // namespace MACE::Core::DataModel::Hit
