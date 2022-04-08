#pragma once

#include "Core/DataFactory.hxx"
#include "Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "Core/DataModel/ITransientData.hxx"

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
    template<typename Vector2_t>
    void SetHitPosition(Vector2_t&& pos) { fHitPosition = std::forward<Vector2_t>(pos); }
    void SetHitPosition(Double_t x, Double_t y) { fHitPosition = {x, y}; }
    template<typename Vector2_t>
    void SetHitPositionVariance(Vector2_t&& posVar) { fHitPositionVariance = std::forward<Vector2_t>(posVar); }
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
