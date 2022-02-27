#pragma once

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

#include "SimMACE/Global.hxx"
#include "DataModel/SimHit/CalorimeterSimHit.hxx"

class MACE::SimMACE::CalorimeterHit final :
    public G4VHit,
    public MACE::DataModel::CalorimeterSimHit {
public:
    CalorimeterHit() noexcept = default;
    CalorimeterHit(const CalorimeterHit& hit) noexcept = default;
    CalorimeterHit(CalorimeterHit&& hit) noexcept = default;
    ~CalorimeterHit() noexcept = default;
    CalorimeterHit& operator=(const CalorimeterHit& hit) noexcept = default;
    CalorimeterHit& operator=(CalorimeterHit&& hit) noexcept = default;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

private:
    static G4Allocator<CalorimeterHit> fgCalorimeterHitAllocator;
};

namespace MACE::SimMACE::Hit {
    using CalorimeterHitCollection = G4THitsCollection<CalorimeterHit>;
}

inline void* MACE::SimMACE::CalorimeterHit::
operator new(size_t) {
    return static_cast<void*>(fgCalorimeterHitAllocator.MallocSingle());
}

inline void MACE::SimMACE::CalorimeterHit::
operator delete(void* hit) {
    fgCalorimeterHitAllocator.FreeSingle(static_cast<CalorimeterHit*>(hit));
}
