#pragma once

#include "TEveVector.h"

#include "DataModel/Global.hxx"
#include "DataModel/Interface/Data.hxx"

class MACE::DataModel::SpectrometerHit :
    public MACE::DataModel::Interface::Data {
    friend MACE::DataModel::DataHub;

public:
    SpectrometerHit() noexcept;
    SpectrometerHit(const SpectrometerHit& hit) noexcept = default;
    SpectrometerHit(SpectrometerHit&& hit) noexcept = default;
    virtual ~SpectrometerHit() noexcept = default;
    SpectrometerHit& operator=(const SpectrometerHit& hit) noexcept = default;
    SpectrometerHit& operator=(SpectrometerHit&& hit) noexcept = default;

    [[nodiscard]] const auto& GetHitTime() const { return fHitTime; }
    [[nodiscard]] const auto& GetWirePosition() const { return fWirePosition; }
    [[nodiscard]] const auto& GetDriftDistance() const { return fDriftDistance; }
    [[nodiscard]] const auto& GetDriftDistanceVariance() const { return fDriftDistanceVariance; }
    [[nodiscard]] const auto& GetHitPositionZ() const { return fHitPositionZ; }
    [[nodiscard]] const auto& GetHitPositionZVariance() const { return fHitPositionZVariance; }
    [[nodiscard]] const auto& GetCellID() const { return fCellID; }
    [[nodiscard]] const auto& GetLayerID() const { return fLayerID; }

    void SetHitTime(Double_t val) { fHitTime = val; }
    void SetWirePosition(const TEveVector2D& val) { fWirePosition = val; }
    void SetWirePosition(TEveVector2D&& val) { fWirePosition = std::move(val); }
    void SetWirePosition(Double_t x, Double_t y) { fWirePosition.fX = x; fWirePosition.fY = y; }
    void SetDriftDistance(Double_t d) { fDriftDistance = d; }
    void SetDriftDistanceVariance(Double_t var) { fDriftDistanceVariance = var; }
    void SetHitPositionZ(Double_t z) { fHitPositionZ = z; }
    void SetHitPositionZVariance(Double_t var) { fHitPositionZVariance = var; }
    void SetCellID(Int_t val) { fCellID = val; }
    void SetLayerID(Int_t val) { fLayerID = val; }

protected:
    static void CreateBranches(TTree& tree);
    inline void FillBranchVariables() const noexcept;
    static void ReadBranches(TTree& tree);

private:
    static constexpr const char* BasicName() { return "CDCHit"; }

private:
    Double_t fHitTime;
    TEveVector2D fWirePosition;
    Double_t fDriftDistance;
    Double_t fDriftDistanceVariance;
    Double_t fHitPositionZ;
    Double_t fHitPositionZVariance;
    Int_t fCellID;
    Int_t fLayerID;

    static Column<Float_t> fgHitTime;
    static Column<Float_t> fgWirePositionX;
    static Column<Float_t> fgWirePositionY;
    static Column<Float_t> fgDriftDistance;
    static Column<Float_t> fgDriftDistanceVariance;
    static Column<Float_t> fgHitPositionZ;
    static Column<Float_t> fgHitPositionZVariance;
    static Column<Int_t> fgCellID;
    static Column<Int_t> fgLayerID;
};

inline void MACE::DataModel::SpectrometerHit::FillBranchVariables() const noexcept {
    Interface::Data::FillBranchVariables();
    fgHitTime.value = fHitTime;
    fgWirePositionX.value = fWirePosition.fX;
    fgWirePositionY.value = fWirePosition.fY;
    fgDriftDistance.value = fDriftDistance;
    fgHitPositionZ.value = fHitPositionZ;
    fgCellID.value = fCellID;
    fgLayerID.value = fLayerID;
}
