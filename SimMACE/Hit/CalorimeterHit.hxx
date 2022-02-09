#pragma once

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

#include "SimMACE/Global.hxx"
#include "DataModel/SimHit/CalorimeterSimHit.hxx"

class MACE::SimMACE::Hit::CalorimeterHit final :
    public G4VHit,
    public MACE::DataModel::CalorimeterSimHit {
public:
    CalorimeterHit() noexcept;
    CalorimeterHit(const CalorimeterHit& hit) noexcept;
    CalorimeterHit(CalorimeterHit&& hit) noexcept;
    ~CalorimeterHit() noexcept {}
    CalorimeterHit& operator=(const CalorimeterHit& hit) noexcept;
    CalorimeterHit& operator=(CalorimeterHit&& hit) noexcept;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

private:
    static G4Allocator<CalorimeterHit> fgCalorimeterHitAllocator;
};

namespace MACE::SimMACE::Hit {
    using CalorimeterHitCollection = G4THitsCollection<CalorimeterHit>;
}

inline void* MACE::SimMACE::Hit::CalorimeterHit::
operator new(size_t) {
    return static_cast<void*>(fgCalorimeterHitAllocator.MallocSingle());
}

inline void MACE::SimMACE::Hit::CalorimeterHit::
operator delete(void* hit) {
    fgCalorimeterHitAllocator.FreeSingle(static_cast<CalorimeterHit*>(hit));
}
