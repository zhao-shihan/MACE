#pragma once

#include "MACE/DataModel/SimHit/EMCalSimHit.h++"
#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::SimMACE::inline Hit {

class EMCalHit final : public DataModel::EMCalSimHit,
                       public Geant4X::UseG4Allocator<EMCalHit>,
                       public G4VHit {};
static_assert(DataModel::TransientData<EMCalHit>);

using EMCalHitCollection = G4THitsCollection<EMCalHit>;

} // namespace MACE::SimMACE::inline Hit
