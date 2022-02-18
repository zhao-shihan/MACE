#pragma once

#include "TEveVector.h"

#include "DataModel/Global.hxx"
#include "DataModel/Interface/Data.hxx"

class MACE::DataModel::VertexDetectorHit :
    public MACE::DataModel::Interface::Data {
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

    void SetHitTime(Double_t val) { fHitTime = val; }
    void SetHitPosition(const TEveVectorD& val) { fHitPosition = val; }
    void SetHitPosition(TEveVectorD&& val) { fHitPosition = std::move(val); }
    void SetHitPosition(Double_t x, Double_t y, Double_t z) { fHitPosition.Set(x, y, z); }

protected:
    static void CreateBranches(TTree& tree);
    inline void FillBranchVariables() const noexcept;
    static void ReadBranches(TTree& tree);

private:
    static constexpr const char* BasicName() { return "MCPHit"; }

private:
    Double_t fHitTime;
    TEveVectorD fHitPosition;

    static Column<Float_t> fgHitTime;
    static Column<TEveVectorF> fgHitPosition;
};

inline void MACE::DataModel::VertexDetectorHit::FillBranchVariables() const noexcept {
    Interface::Data::FillBranchVariables();
    fgHitTime.value = fHitTime;
    fgHitPosition.value = fHitPosition;
}
