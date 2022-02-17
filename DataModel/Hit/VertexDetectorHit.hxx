#pragma once

#include "TEveVector.h"

#include "DataModel/Global.hxx"
#include "DataModel/Interface/Data.hxx"

class MACE::DataModel::VertexDetectorHit :
    private MACE::DataModel::Interface::Data {
public:
    VertexDetectorHit() noexcept;
    VertexDetectorHit(const VertexDetectorHit& hit) noexcept;
    VertexDetectorHit(VertexDetectorHit&& hit) noexcept;
    virtual ~VertexDetectorHit() noexcept = default;
    VertexDetectorHit& operator=(const VertexDetectorHit& hit) noexcept;
    VertexDetectorHit& operator=(VertexDetectorHit&& hit) noexcept;

    static constexpr const char* Name() { return "MCPHit"; }
    static void CreateBranches(const std::shared_ptr<TTree>& tree);
    inline void FillBranches() noexcept;
    static void ReadBranches(TTree* tree);

    [[nodiscard]] const auto& GetHitTime() const { return fHitTime; }
    [[nodiscard]] const auto& GetHitPosition() const { return fHitPosition; }

    void SetHitTime(Double_t val) { fHitTime = val; }
    void SetHitPosition(const TEveVectorD& val) { fHitPosition = val; }
    void SetHitPosition(TEveVectorD&& val) { fHitPosition = std::move(val); }
    void SetHitPosition(Double_t x, Double_t y, Double_t z) { fHitPosition.fX = x; fHitPosition.fY = y; fHitPosition.fZ = z; }

private:
    Double_t fHitTime;
    TEveVectorD fHitPosition;

    static Column<Float_t> fgHitTime;
    static Column<Float_t> fgHitPositionX;
    static Column<Float_t> fgHitPositionY;
    static Column<Float_t> fgHitPositionZ;
};

inline void MACE::DataModel::VertexDetectorHit::FillBranches() noexcept {
    Interface::Data::FillBranches();
    fgHitTime.value = fHitTime;
    fgHitPositionX.value = fHitPosition.fX;
    fgHitPositionY.value = fHitPosition.fY;
    fgHitPositionZ.value = fHitPosition.fZ;
}