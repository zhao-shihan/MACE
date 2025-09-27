#pragma once

#include "MACE/Data/SensorHit.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Geant4X/Memory/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::inline Simulation::inline Hit {

class VetoPMHit final : public Mustard::Geant4X::UseG4Allocator<VetoPMHit>,
                        public G4VHit,
                        public Mustard::Data::Tuple<Data::VetoPMHit> {};

using VetoPMHitCollection = G4THitsCollection<VetoPMHit>;

} // namespace MACE::inline Simulation::inline Hit