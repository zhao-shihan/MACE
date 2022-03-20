#pragma once

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4VHit.hh"

#include "DataModel/SimHit/CalorimeterSimHit.hxx"
#include "ObserverPtr.hxx"
#include "SimMACE/Global.hxx"

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
    inline void operator delete(void*);

private:
    static ObserverPtr<G4Allocator<CalorimeterHit>> fgCalorimeterHitAllocator;
};

namespace MACE::SimMACE::inline Hit {

using CalorimeterHitCollection = G4THitsCollection<CalorimeterHit>;

inline void* CalorimeterHit::operator new(size_t) {
    if (fgCalorimeterHitAllocator == nullptr) {
        fgCalorimeterHitAllocator = new G4Allocator<CalorimeterHit>();
    }
    return static_cast<void*>(fgCalorimeterHitAllocator->MallocSingle());
}

inline void CalorimeterHit::operator delete(void* hit) {
    fgCalorimeterHitAllocator->FreeSingle(static_cast<CalorimeterHit*>(hit));
}

}
