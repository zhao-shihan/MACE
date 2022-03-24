#pragma once

#include "DataModel/SimHit/VertexDetectorSimHit.hxx"
#include "ObserverPtr.hxx"
#include "SimMACE/Global.hxx"

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VHit.hh"

namespace MACE::Simulation::SimMACE::Hit {

using Utility::ObserverPtr;

class VertexDetectorHit final : public G4VHit,
                                public Core::DataModel::SimHit::VertexDetectorSimHit {
    using Base = VertexDetectorSimHit;

public:
    VertexDetectorHit() noexcept = default;
    VertexDetectorHit(const VertexDetectorHit& hit) noexcept = default;
    VertexDetectorHit(VertexDetectorHit&& hit) noexcept = default;
    ~VertexDetectorHit() noexcept = default;
    VertexDetectorHit& operator=(const VertexDetectorHit& hit) noexcept = default;
    VertexDetectorHit& operator=(VertexDetectorHit&& hit) noexcept = default;

    void SetHitPosition(const G4TwoVector& pos) { Base::SetHitPosition(pos.x(), pos.y()); }
    void SetVertexPosition(const G4ThreeVector& pos) { Base::SetVertexPosition(pos.x(), pos.y(), pos.z()); }

    inline void* operator new(size_t);
    inline void operator delete(void*);

private:
    static ObserverPtr<G4Allocator<VertexDetectorHit>> fgVertexDetectorAllocator;
};

using VertexDetectorHitCollection = G4THitsCollection<VertexDetectorHit>;

inline void* VertexDetectorHit::operator new(size_t) {
    if (fgVertexDetectorAllocator == nullptr) {
        fgVertexDetectorAllocator = new G4Allocator<VertexDetectorHit>();
    }
    return static_cast<void*>(fgVertexDetectorAllocator->MallocSingle());
}

inline void VertexDetectorHit::operator delete(void* hit) {
    fgVertexDetectorAllocator->FreeSingle(static_cast<VertexDetectorHit*>(hit));
}

} // namespace MACE::Simulation::SimMACE::Hit
