#pragma once

#include "G4VHit.hh"

#include "SimG4Global.hh"

#include "hit/Calorimeter.hh"

class MACE::SimG4::Hit::Calorimeter final :
    public G4VHit,
    public MACE::DataModel::Hit::Calorimeter{
    MACE_DATA_MODEL_CONSTRUCTORS_AND_ASSIGNMENTS(Calorimeter);

    MACE_DATA_MODEL_LARGE_MEMBER(TString, ParticleName);
    MACE_DATA_MODEL_SMALL_MEMBER(int32_t, TrackID);

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

    using CollectionOfCalorimeter = G4THitsCollection<Calorimeter>;

    extern G4Allocator<Calorimeter>* AllocatorOfCalorimeter;

    inline void* Calorimeter::operator new(size_t) {
        return static_cast<void*>(AllocatorOfCalorimeter->MallocSingle());
    }

    inline void Calorimeter::operator delete(void* hit) {
        AllocatorOfCalorimeter->FreeSingle(static_cast<Calorimeter*>(hit));
    }

}
