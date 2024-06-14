#pragma once

#include "MACE/Data/SimHit.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Extension/Geant4X/Memory/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::inline Simulation::inline Hit {

class CDCHit final : public Geant4X::UseG4Allocator<CDCHit>,
                     public G4VHit,
                     public Data::Tuple<Data::CDCSimHit> {};

using CDCHitCollection = G4THitsCollection<CDCHit>;

} // namespace MACE::inline Simulation::inline Hit
