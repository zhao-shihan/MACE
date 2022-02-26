#pragma once

#include "TEveVector.h"

#include "DataModel/Interface/Data.hxx"
#include "DataModel/BranchSocket/BasicBranchSocket.hxx"
#include "DataModel/BranchSocket/ClassBranchSocket.hxx"

class MACE::DataModel::VertexDetectorHit :
    public MACE::DataModel::Interface::Data {
    using Base = MACE::DataModel::Interface::Data;
    friend MACE::DataModel::DataHub;

public:
    VertexDetectorHit() noexcept;
    VertexDetectorHit(const VertexDetectorHit& hit) noexcept = default;
    VertexDetectorHit(VertexDetectorHit&& hit) noexcept = default;
    virtual ~VertexDetectorHit() noexcept = default;
    VertexDetectorHit& operator=(const VertexDetectorHit& hit) noexcept = default;
    VertexDetectorHit& operator=(VertexDetectorHit&& hit) noexcept = default;

    [[nodiscard]] const auto& GetHitTime() const { return fHitTime; }
    [[nodiscard]] const auto& GetHitPosition() const { return fHitPosition; }
    [[nodiscard]] const auto& GetHitPositionVariance() const { return fHitPositionVariance; }

    void SetHitTime(Double_t val) { fHitTime = val; }
    void SetHitPosition(const TEveVector2D& val) { fHitPosition = val; }
    void SetHitPosition(TEveVector2D&& val) { fHitPosition = std::move(val); }
    void SetHitPosition(Double_t x, Double_t y) { fHitPosition.Set(x, y); }
    void SetHitPositionVariance(const TEveVector2D& val) { fHitPositionVariance = val; }
    void SetHitPositionVariance(TEveVector2D&& val) { fHitPositionVariance = std::move(val); }
    void SetHitPositionVariance(Double_t xVar, Double_t yVar) { fHitPositionVariance.Set(xVar, yVar); }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    inline void FillBranchSockets() const noexcept;

private:
    static constexpr const char* BasicName() { return "MCPHit"; }

private:
    Double_t     fHitTime;
    TEveVector2D fHitPosition;
    TEveVector2D fHitPositionVariance;

    static FloatBranchSocket    fgHitTime;
    static Vector2FBranchSocket fgHitPosition;
    static Vector2FBranchSocket fgHitPositionVariance;
};

inline void MACE::DataModel::VertexDetectorHit::FillBranchSockets() const noexcept {
    Base::FillBranchSockets();
    fgHitTime.Value() = fHitTime;
    fgHitPosition.Value() = fHitPosition;
    fgHitPositionVariance.Value() = fHitPositionVariance;
}
