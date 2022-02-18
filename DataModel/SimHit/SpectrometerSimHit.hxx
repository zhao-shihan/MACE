#pragma once

#include "DataModel/Global.hxx"
#include "DataModel/Hit/SpectrometerHit.hxx"

class MACE::DataModel::SpectrometerSimHit :
    public MACE::DataModel::SpectrometerHit {
    friend MACE::DataModel::DataHub;

public:
    SpectrometerSimHit() noexcept;
    SpectrometerSimHit(const SpectrometerSimHit& hit) noexcept = default;
    SpectrometerSimHit(SpectrometerSimHit&& hit) noexcept = default;
    virtual ~SpectrometerSimHit() noexcept = default;
    SpectrometerSimHit& operator=(const SpectrometerSimHit& hit) noexcept = default;
    SpectrometerSimHit& operator=(SpectrometerSimHit&& hit) noexcept = default;

    [[nodiscard]] const auto& GetVertexTime() const { return fVertexTime; }
    [[nodiscard]] const auto& GetVertexPosition() const { return fVertexPosition; }
    [[nodiscard]] const auto& GetParticlePDGCode() const { return fPDGCode; }
    [[nodiscard]] const auto& GetTrackID() const { return fTrackID; }

    void SetVertexTime(Double_t val) { fVertexTime = val; }
    void SetVertexPosition(const TEveVectorD& pos) { fVertexPosition = pos; }
    void SetVertexPosition(TEveVectorD&& pos) { fVertexPosition = std::move(pos); }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition.fX = x; fVertexPosition.fY = y; fVertexPosition.fZ = z; }
    void SetPDGCode(Int_t pdgCode) { fPDGCode = pdgCode; }
    void SetTrackID(Int_t val) { fTrackID = val; }

protected:
    static void CreateBranches(TTree& tree);
    inline void FillBranchVariables() const noexcept;
    static void ReadBranches(TTree& tree);

private:
    static constexpr const char* BasicName() { return "CDCSimHit"; }

private:
    Double_t fVertexTime;
    TEveVectorD fVertexPosition;
    Int_t fPDGCode;
    Int_t fTrackID;

    static Column<Float_t> fgVertexTime;
    static Column<Float_t> fgVertexPositionX;
    static Column<Float_t> fgVertexPositionY;
    static Column<Float_t> fgVertexPositionZ;
    static Column<Int_t> fgPDGCode;
    static Column<Int_t> fgTrackID;
};

inline void MACE::DataModel::SpectrometerSimHit::FillBranchVariables() const noexcept {
    SpectrometerHit::FillBranchVariables();
    fgVertexTime.value = fVertexTime;
    fgVertexPositionX.value = fVertexPosition.fX;
    fgVertexPositionY.value = fVertexPosition.fY;
    fgVertexPositionZ.value = fVertexPosition.fZ;
    fgPDGCode.value = fPDGCode;
    fgTrackID.value = fTrackID;
}
