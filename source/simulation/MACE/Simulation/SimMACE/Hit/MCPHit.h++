#pragma once

#include "MACE/DataModel/SimHit/MCPSimHit.h++"
#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::inline Simulation::SimMACE::inline Hit {

class MCPHit final : public DataModel::MCPSimHit,
                     public Geant4X::UseG4Allocator<MCPHit>,
                     public G4VHit {};
static_assert(DataModel::TransientData<MCPHit>);

using MCPHitCollection = G4THitsCollection<MCPHit>;

} // namespace MACE::inline Simulation::SimMACE::inline Hit
