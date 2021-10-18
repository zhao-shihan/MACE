#pragma once

#include "G4VHit.hh"

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
    const auto& GetParticleName() const { return fParticleName; }
    auto GetTrackID() const { return fTrackID; }

    void SetVertexTime(double_t val) { fVertexTime = val; }
    void SetVertexPosition(const CLHEP::Hep3Vector& pos) { fVertexPosition = pos; }
    void SetVertexPosition(CLHEP::Hep3Vector&& pos) { fVertexPosition = std::move(pos); }
    void SetParticleName(const TString& name) { fParticleName = name; }
    void SetParticleName(TString&& name) { fParticleName = std::move(name); }
    void SetTrackID(int32_t val) { fTrackID = val; }

private:
    double_t fVertexTime;
    CLHEP::Hep3Vector fVertexPosition;
    TString fParticleName;
    int32_t fTrackID;

    static DataModel::Core::Column<Float_t> fgVertexTime;
    static DataModel::Core::Column<Float_t> fgVertexPositionX;
    static DataModel::Core::Column<Float_t> fgVertexPositionY;
    static DataModel::Core::Column<Float_t> fgVertexPositionZ;
    static DataModel::Core::Column<TString> fgParticleName;
    static DataModel::Core::Column<Int_t> fgTrackID;

public:
    inline void* operator new(size_t);
    inline void  operator delete(void*);
};

void MACE::SimG4::Hit::SpectrometerHit::FillBranches() noexcept {
    DataModel::Hit::SpectrometerHit::FillBranches();
    fgVertexTime.value = fVertexTime;
    fgVertexPositionX.value = fVertexPosition.x();
    fgVertexPositionX.value = fVertexPosition.y();
    fgVertexPositionX.value = fVertexPosition.z();
    fgParticleName.value = fParticleName;
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
