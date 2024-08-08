#pragma once

#include "MACE/Data/SimHit.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Extension/Geant4X/Memory/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::inline Simulation::inline Hit {

class ECalHit final : public Mustard::Geant4X::UseG4Allocator<ECalHit>,
                     public G4VHit,
                     public Mustard::Data::Tuple<Data::ECalSimHit> {};

using ECalHitCollection = G4THitsCollection<ECalHit>;

} // namespace MACE::inline Simulation::inline Hit
