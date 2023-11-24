#pragma once

#include "MACE/Data/SimHit.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::SimMACE::inline Hit {

class MCPHit final : public Geant4X::UseG4Allocator<MCPHit>,
                     public G4VHit,
                     public Data::Tuple<Data::MCPSimHit> {};

using MCPHitCollection = G4THitsCollection<MCPHit>;

} // namespace MACE::SimMACE::inline Hit
