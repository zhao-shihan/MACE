#pragma once

#include "DataModel/Interface/Transient.hxx"
#include "DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "DataModel/BranchSocket/Vector2BranchSocket.hxx"

class MACE::DataModel::VertexDetectorHit :
    public MACE::DataModel::Interface::Transient {
    using Base = MACE::DataModel::Interface::Transient;
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
    template<typename Vector2_t>
    void SetHitPosition(Vector2_t&& pos) { fHitPosition = std::forward<Vector2_t>(pos); }
    void SetHitPosition(Double_t x, Double_t y) { fHitPosition.Set(x, y); }
    template<typename Vector2_t>
    void SetHitPositionVariance(Vector2_t&& posVar) { fHitPositionVariance = std::forward<Vector2_t>(posVar); }
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

    static DoubleBranchSocket   fgHitTime;
    static Vector2FBranchSocket fgHitPosition;
    static Vector2FBranchSocket fgHitPositionVariance;
};

inline void MACE::DataModel::VertexDetectorHit::FillBranchSockets() const noexcept {
    Base::FillBranchSockets();
    fgHitTime.SetValue(fHitTime);
    fgHitPosition.SetValue(fHitPosition);
    fgHitPositionVariance.SetValue(fHitPositionVariance);
}
