#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/ITransientData.hxx"

namespace MACE::Core::DataModel::Hit {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::Vector2FBranchSocket;

class MCPHit : public ITransientData {
    using Base = ITransientData;

public:
    MCPHit() noexcept;
    MCPHit(const MCPHit& hit) noexcept = default;
    MCPHit(MCPHit&& hit) noexcept = default;
    virtual ~MCPHit() noexcept = default;
    MCPHit& operator=(const MCPHit& hit) noexcept = default;
    MCPHit& operator=(MCPHit&& hit) noexcept = default;

    const auto& GetHitTime() const { return fHitTime; }
    const auto& GetHitPosition() const { return fHitPosition; }
    const auto& GetHitPositionVariance() const { return fHitPositionVariance; }

    void SetHitTime(Double_t val) { fHitTime = val; }
    template<typename Vector2T>
    void SetHitPosition(Vector2T&& pos) { fHitPosition = std::forward<Vector2T>(pos); }
    void SetHitPosition(Double_t x, Double_t y) { fHitPosition = {x, y}; }
    template<typename Vector2T>
    void SetHitPositionVariance(Vector2T&& posVar) { fHitPositionVariance = std::forward<Vector2T>(posVar); }
    void SetHitPositionVariance(Double_t xVar, Double_t yVar) { fHitPositionVariance = {xVar, yVar}; }

    static consteval const char* BasicTreeName() noexcept { return "MCPHit"; }
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    Double_t fHitTime;
    Eigen::Vector2d fHitPosition;
    Eigen::Vector2d fHitPositionVariance;

    static DoubleBranchSocket fgHitTime;
    static Vector2FBranchSocket fgHitPosition;
    static Vector2FBranchSocket fgHitPositionVariance;
};

} // namespace MACE::Core::DataModel::Hit
