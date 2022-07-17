#pragma once

#include "MACE/Core/DataModel/SimHit/CDCSimHit.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VHit.hh"

namespace MACE::SimMACE::Hit {

using Utility::ObserverPtr;

class CDCHit final : public G4VHit,
                     public Core::DataModel::SimHit::CDCSimHit {
    using Base = CDCSimHit;

public:
    CDCHit() noexcept = default;
    CDCHit(const CDCHit& hit) noexcept = default;
    CDCHit(CDCHit&& hit) noexcept = default;
    ~CDCHit() noexcept = default;
    CDCHit& operator=(const CDCHit& hit) noexcept = default;
    CDCHit& operator=(CDCHit&& hit) noexcept = default;

    inline void* operator new(size_t);
    inline void operator delete(void*);

    void SetWirePosition(const G4TwoVector& pos) { Base::SetWirePosition(pos.x(), pos.y()); }
    void SetWireDirection(const G4ThreeVector& dir) { Base::SetWireDirection(dir.x(), dir.y(), dir.z()); }
    void SetMomentum(const G4ThreeVector& mom) { Base::SetMomentum(mom.x(), mom.y(), mom.z()); }
    void SetVertexPosition(const G4ThreeVector& pos) { Base::SetVertexPosition(pos.x(), pos.y(), pos.z()); }
    void SetVertexMomentum(const G4ThreeVector& mom) { Base::SetVertexMomentum(mom.x(), mom.y(), mom.z()); }

private:
    static ObserverPtr<G4Allocator<CDCHit>> fgCDCHitAllocator;
};

using CDCHitCollection = G4THitsCollection<CDCHit>;

} // namespace MACE::SimMACE::Hit

#include "MACE/SimMACE/Hit/CDCHit.inl"
