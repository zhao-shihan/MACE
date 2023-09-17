#pragma once

#include "MACE/DataModel/SimHit/EMCSimHit.h++"
#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::inline Simulation::SimMACE::inline Hit {

class EMCHit final : public DataModel::EMCSimHit,
                       public Geant4X::UseG4Allocator<EMCHit>,
                       public G4VHit {};
static_assert(DataModel::TransientData<EMCHit>);

using EMCHitCollection = G4THitsCollection<EMCHit>;

} // namespace MACE::inline Simulation::SimMACE::inline Hit
