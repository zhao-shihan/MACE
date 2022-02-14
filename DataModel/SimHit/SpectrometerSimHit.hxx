#pragma once

#include "DataModel/Global.hxx"
#include "DataModel/Hit/SpectrometerHit.hxx"

class MACE::DataModel::SpectrometerSimHit :
    public MACE::DataModel::SpectrometerHit {
public:
    SpectrometerSimHit() noexcept;
    SpectrometerSimHit(const SpectrometerSimHit& hit) noexcept;
    SpectrometerSimHit(SpectrometerSimHit&& hit) noexcept;
    virtual ~SpectrometerSimHit() noexcept = default;
    SpectrometerSimHit& operator=(const SpectrometerSimHit& hit) noexcept;
    SpectrometerSimHit& operator=(SpectrometerSimHit&& hit) noexcept;

    static void CreateBranches(TTree* tree);
    inline void FillBranches() noexcept;
    static void ReadBranches(TTree* tree);

    const auto& GetVertexTime() const { return fVertexTime; }
    const auto& GetVertexPosition() const { return fVertexPosition; }
    const auto& GetParticlePDGCode() const { return fPDGCode; }
    const auto& GetTrackID() const { return fTrackID; }

    void SetVertexTime(Double_t val) { fVertexTime = val; }
    void SetVertexPosition(const TEveVectorD& pos) { fVertexPosition = pos; }
    void SetVertexPosition(TEveVectorD&& pos) { fVertexPosition = std::move(pos); }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition.fX = x; fVertexPosition.fY = y; fVertexPosition.fZ = z; }
    void SetPDGCode(Int_t pdgCode) { fPDGCode = pdgCode; }
    void SetTrackID(Int_t val) { fTrackID = val; }

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

inline void MACE::DataModel::SpectrometerSimHit::FillBranches() noexcept {
    SpectrometerHit::FillBranches();
    fgVertexTime.value = fVertexTime;
    fgVertexPositionX.value = fVertexPosition.fX;
    fgVertexPositionY.value = fVertexPosition.fY;
    fgVertexPositionZ.value = fVertexPosition.fZ;
    fgPDGCode.value = fPDGCode;
    fgTrackID.value = fTrackID;
}
