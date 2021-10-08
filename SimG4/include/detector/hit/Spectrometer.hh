#pragma once

#include "G4VHit.hh"

#include "SimG4Global.hh"

#include "hit/Spectrometer.hh"

class MACE::SimG4::Hit::Spectrometer :
    public G4VHit,
    public MACE::DataModel::Hit::Spectrometer {
    MACE_DATA_MODEL_CONSTRUCTORS_AND_ASSIGNMENTS(Spectrometer);

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

    using CollectionOfSpectrometer = G4THitsCollection<Spectrometer>;

    extern G4Allocator<Spectrometer>* AllocatorOfSpectrometer;

    inline void* Spectrometer::operator new(size_t) {
        return static_cast<void*>(AllocatorOfSpectrometer->MallocSingle());
    }

    inline void Spectrometer::operator delete(void* hit) {
        AllocatorOfSpectrometer->FreeSingle(static_cast<Spectrometer*>(hit));
    }

}
