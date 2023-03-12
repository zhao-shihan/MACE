#pragma once

#include "MACE/Core/DataModel/SimHit/CDCSimHit.hxx"
#include "MACE/Extension/Geant4X/UseG4Allocator.hxx"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::SimMACE::Hit {

class CDCHit final : public Core::DataModel::SimHit::CDCSimHit,
                     public Geant4X::UseG4Allocator<CDCHit>,
                     public G4VHit {
public:
    CDCHit() noexcept = default;
    ~CDCHit() = default;

    CDCHit(const CDCHit& hit) noexcept = default;
    CDCHit(CDCHit&& hit) noexcept = default;
    CDCHit& operator=(const CDCHit& hit) noexcept = default;
    CDCHit& operator=(CDCHit&& hit) noexcept = default;
};
static_assert(Core::DataModel::TransientData<CDCHit>);

using CDCHitCollection = G4THitsCollection<CDCHit>;

} // namespace MACE::SimMACE::Hit
