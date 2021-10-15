#pragma once

#include "G4VHit.hh"

#include "SimG4/Global.hh"

#include "DataModel/Hit/SpectrometerHit.hh"

class MACE::SimG4::Hit::SpectrometerHit :
    public G4VHit,
    public MACE::DataModel::Hit::SpectrometerHit {
    MACE_DATA_MODEL_CONSTRUCTORS_AND_ASSIGNMENTS(SpectrometerHit);

    MACE_DATA_MODEL_SMALL_MEMBER(double_t, VertexTime);
    MACE_DATA_MODEL_LARGE_MEMBER(CLHEP::Hep3Vector, VertexPosition);
    MACE_DATA_MODEL_LARGE_MEMBER(TString, ParticleName);
    MACE_DATA_MODEL_SMALL_MEMBER(int32_t, TrackID);

    MACE_DATA_MODEL_PERSISTIFIER(Float_t, VertexTime);
    MACE_DATA_MODEL_PERSISTIFIER(Float_t, VertexPositionX);
    MACE_DATA_MODEL_PERSISTIFIER(Float_t, VertexPositionY);
    MACE_DATA_MODEL_PERSISTIFIER(Float_t, VertexPositionZ);
    MACE_DATA_MODEL_PERSISTIFIER(TString, ParticleName);
    MACE_DATA_MODEL_PERSISTIFIER(Int_t, TrackID);

public:
    static void CreateBranches(TTree* tree);
    void FillBranches() override;

    inline void* operator new(size_t);
    inline void  operator delete(void*);
};

#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

namespace MACE::SimG4::Hit {

    using CollectionOfSpectrometer = G4THitsCollection<SpectrometerHit>;

    extern G4Allocator<SpectrometerHit>* AllocatorOfSpectrometer;

    inline void* SpectrometerHit::operator new(size_t) {
        return static_cast<void*>(AllocatorOfSpectrometer->MallocSingle());
    }

    inline void SpectrometerHit::operator delete(void* hit) {
        AllocatorOfSpectrometer->FreeSingle(static_cast<SpectrometerHit*>(hit));
    }

}
