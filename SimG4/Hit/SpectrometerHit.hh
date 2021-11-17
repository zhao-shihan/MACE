#pragma once

#include "G4VHit.hh"
#include "G4ThreeVector.hh"

#include "SimG4/Global.hh"
#include "DataModel/Hit/SpectrometerHit.hh"

class MACE::SimG4::Hit::SpectrometerHit :
    public G4VHit,
    public MACE::DataModel::Hit::SpectrometerHit {
public:
    SpectrometerHit() noexcept;
    SpectrometerHit(const SpectrometerHit& hit) noexcept;
    SpectrometerHit(SpectrometerHit&& hit) noexcept;
    ~SpectrometerHit() noexcept {}
    SpectrometerHit& operator=(const SpectrometerHit& hit) noexcept;
    SpectrometerHit& operator=(SpectrometerHit&& hit) noexcept;

    static void CreateBranches(TTree* tree);
    inline void FillBranches() noexcept;
    static void ReadBranches(TTree* tree);

    auto GetVertexTime() const { return fVertexTime; }
    const auto& GetVertexPosition() const { return fVertexPosition; }
    const auto& GetParticlePDGCode() const { return fPDGCode; }
    auto GetTrackID() const { return fTrackID; }

    using DataModel::Hit::SpectrometerHit::SetHitPosition;
    void SetHitPosition(const G4ThreeVector& pos) { SetHitPosition(pos.x(), pos.y(), pos.z()); }
    void SetVertexTime(double_t val) { fVertexTime = val; }
    void SetVertexPosition(const TEveVectorD& pos) { fVertexPosition = pos; }
    void SetVertexPosition(TEveVectorD&& pos) { fVertexPosition = std::move(pos); }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition.fX = x; fVertexPosition.fY = y; fVertexPosition.fZ = z; }
    void SetVertexPosition(const G4ThreeVector& pos) { SetVertexPosition(pos.x(), pos.y(), pos.z()); }
    void SetPDGCode(Int_t pdgCode) { fPDGCode = pdgCode; }
    void SetTrackID(Int_t val) { fTrackID = val; }

private:
    double_t fVertexTime;
    TEveVectorD fVertexPosition;
    Int_t fPDGCode;
    Int_t fTrackID;

    static DataModel::Column<Float_t> fgVertexTime;
    static DataModel::Column<Float_t> fgVertexPositionX;
    static DataModel::Column<Float_t> fgVertexPositionY;
    static DataModel::Column<Float_t> fgVertexPositionZ;
    static DataModel::Column<Int_t> fgPDGCode;
    static DataModel::Column<Int_t> fgTrackID;

public:
    inline void* operator new(size_t);
    inline void  operator delete(void*);
};

void MACE::SimG4::Hit::SpectrometerHit::FillBranches() noexcept {
    DataModel::Hit::SpectrometerHit::FillBranches();
    fgVertexTime.value = fVertexTime;
    fgVertexPositionX.value = fVertexPosition.fX;
    fgVertexPositionY.value = fVertexPosition.fY;
    fgVertexPositionZ.value = fVertexPosition.fZ;
    fgPDGCode.value = fPDGCode;
    fgTrackID.value = fTrackID;
}

#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

namespace MACE::SimG4::Hit {

    using SpectrometerHitCollection = G4THitsCollection<SpectrometerHit>;

    extern G4Allocator<SpectrometerHit>* SpectrometerHitAllocator;

    inline void* SpectrometerHit::operator new(size_t) {
        return static_cast<void*>(SpectrometerHitAllocator->MallocSingle());
    }

    inline void SpectrometerHit::operator delete(void* hit) {
        SpectrometerHitAllocator->FreeSingle(static_cast<SpectrometerHit*>(hit));
    }

}
