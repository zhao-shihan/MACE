#pragma once

#include "MACE/Data/SimHit.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::inline Simulation::inline Hit {

class STCHit final : public Geant4X::UseG4Allocator<STCHit>,
                     public G4VHit,
                     public Data::Tuple<Data::STCSimHit> {};

using STCHitCollection = G4THitsCollection<STCHit>;

} // namespace MACE::inline Simulation::inline Hit
