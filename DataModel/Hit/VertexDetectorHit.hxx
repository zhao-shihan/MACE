#pragma once

#include "TEveVector.h"

#include "DataModel/Global.hxx"
#include "DataModel/Interface/Data.hxx"

class MACE::DataModel::VertexDetectorHit :
    public MACE::DataModel::Interface::Data {
    friend MACE::DataModel::DataHub;

public:
    VertexDetectorHit() noexcept;
    VertexDetectorHit(const VertexDetectorHit& hit) noexcept;
    VertexDetectorHit(VertexDetectorHit&& hit) noexcept;
    virtual ~VertexDetectorHit() noexcept = default;
    VertexDetectorHit& operator=(const VertexDetectorHit& hit) noexcept;
    VertexDetectorHit& operator=(VertexDetectorHit&& hit) noexcept;

    [[nodiscard]] const auto& GetHitTime() const { return fHitTime; }
    [[nodiscard]] const auto& GetHitPosition() const { return fHitPosition; }

    void SetHitTime(Double_t val) { fHitTime = val; }
    void SetHitPosition(const TEveVectorD& val) { fHitPosition = val; }
    void SetHitPosition(TEveVectorD&& val) { fHitPosition = std::move(val); }
    void SetHitPosition(Double_t x, Double_t y, Double_t z) { fHitPosition.fX = x; fHitPosition.fY = y; fHitPosition.fZ = z; }

protected:
    static constexpr const char* Name() { return "MCPHit"; }
    static void CreateBranches(TTree& tree);
    inline void FillBranchVariables() const noexcept;
    static void ReadBranches(TTree& tree);

private:
    Double_t fHitTime;
    TEveVectorD fHitPosition;

    static Column<Float_t> fgHitTime;
    static Column<Float_t> fgHitPositionX;
    static Column<Float_t> fgHitPositionY;
    static Column<Float_t> fgHitPositionZ;
};

inline void MACE::DataModel::VertexDetectorHit::FillBranchVariables() const noexcept {
    Interface::Data::FillBranchVariables();
    fgHitTime.value = fHitTime;
    fgHitPositionX.value = fHitPosition.fX;
    fgHitPositionY.value = fHitPosition.fY;
    fgHitPositionZ.value = fHitPosition.fZ;
}