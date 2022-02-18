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
    VertexDetectorHit() noexcept = default;
    VertexDetectorHit(const VertexDetectorHit& hit) noexcept = default;
    VertexDetectorHit(VertexDetectorHit&& hit) noexcept = default;
    ~VertexDetectorHit() noexcept = default;
    VertexDetectorHit& operator=(const VertexDetectorHit& hit) noexcept = default;
    VertexDetectorHit& operator=(VertexDetectorHit&& hit) noexcept = default;

    void SetHitPosition(const G4ThreeVector& pos) { DataModel::VertexDetectorSimHit::SetHitPosition(pos.x(), pos.y()); }
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
