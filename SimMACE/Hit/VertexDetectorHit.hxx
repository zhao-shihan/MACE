#pragma once

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

#include "SimMACE/Global.hxx"
#include "DataModel/SimHit/VertexDetectorSimHit.hxx"

class MACE::SimMACE::Hit::VertexDetectorHit final :
    public G4VHit,
    public MACE::DataModel::VertexDetectorSimHit {
public:
    VertexDetectorHit() noexcept;
    VertexDetectorHit(const VertexDetectorHit& hit) noexcept;
    VertexDetectorHit(VertexDetectorHit&& hit) noexcept;
    ~VertexDetectorHit() noexcept {}
    VertexDetectorHit& operator=(const VertexDetectorHit& hit) noexcept;
    VertexDetectorHit& operator=(VertexDetectorHit&& hit) noexcept;

    void SetHitPosition(const G4ThreeVector& pos) { DataModel::VertexDetectorSimHit::SetHitPosition(pos.x(), pos.y(), pos.z()); }
    void SetVertexPosition(const G4ThreeVector& pos) { DataModel::VertexDetectorSimHit::SetVertexPosition(pos.x(), pos.y(), pos.z()); }

    inline void* operator new(size_t);
    inline void  operator delete(void*);

private:
    static G4Allocator<VertexDetectorHit> fgVertexDetectorAllocator;
};

namespace MACE::SimMACE::Hit {
    using VertexDetectorHitCollection = G4THitsCollection<VertexDetectorHit>;
}

inline void* MACE::SimMACE::Hit::VertexDetectorHit::
operator new(size_t) {
    return static_cast<void*>(fgVertexDetectorAllocator.MallocSingle());
}

inline void MACE::SimMACE::Hit::VertexDetectorHit::
operator delete(void* hit) {
    fgVertexDetectorAllocator.FreeSingle(static_cast<VertexDetectorHit*>(hit));
}
