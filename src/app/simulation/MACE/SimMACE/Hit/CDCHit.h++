#pragma once

#include "MACE/DataModel/SimHit/CDCSimHit.h++"
#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::SimMACE::inline Hit {

class CDCHit final : public Geant4X::UseG4Allocator<CDCHit>,
                     public G4VHit,
                     public DataModel::CDCSimHit {};
static_assert(DataModel::TransientData<CDCHit>);

using CDCHitCollection = G4THitsCollection<CDCHit>;

} // namespace MACE::SimMACE::inline Hit
