#pragma once

#include "MACE/Core/DataModel/SimHit/CDCSimHit.hxx"
#include "MACE/Geant4X/UseG4Allocator.hxx"

#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VHit.hh"

namespace MACE::SimMACE::Hit {

class CDCHit final : public Geant4X::UseG4Allocator<CDCHit>,
                     public G4VHit,
                     public Core::DataModel::SimHit::CDCSimHit {
public:
    CDCHit() noexcept = default;
    CDCHit(const CDCHit& hit) noexcept = default;
    CDCHit(CDCHit&& hit) noexcept = default;
    ~CDCHit() noexcept = default;
    CDCHit& operator=(const CDCHit& hit) noexcept = default;
    CDCHit& operator=(CDCHit&& hit) noexcept = default;

    void WirePosition(const G4TwoVector& pos) { CDCSimHit::WirePosition(pos.x(), pos.y()); }
    void SetWireDirection(const G4ThreeVector& dir) { CDCSimHit::SetWireDirection(dir.x(), dir.y(), dir.z()); }
    void SetMomentum(const G4ThreeVector& mom) { CDCSimHit::SetMomentum(mom.x(), mom.y(), mom.z()); }
    void SetVertexPosition(const G4ThreeVector& pos) { CDCSimHit::SetVertexPosition(pos.x(), pos.y(), pos.z()); }
    void SetVertexMomentum(const G4ThreeVector& mom) { CDCSimHit::SetVertexMomentum(mom.x(), mom.y(), mom.z()); }
};

using CDCHitCollection = G4THitsCollection<CDCHit>;

} // namespace MACE::SimMACE::Hit
