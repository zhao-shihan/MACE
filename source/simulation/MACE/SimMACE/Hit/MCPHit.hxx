#pragma once

#include "MACE/DataModel/SimHit/MCPSimHit.hxx"
#include "MACE/Extension/Geant4X/UseG4Allocator.hxx"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::SimMACE::inline Hit {

class MCPHit final : public DataModel::MCPSimHit,
                     public Geant4X::UseG4Allocator<MCPHit>,
                     public G4VHit {};
static_assert(DataModel::TransientData<MCPHit>);

using MCPHitCollection = G4THitsCollection<MCPHit>;

} // namespace MACE::SimMACE::inline Hit
