#pragma once

#include "MACE/Data/SensorHit.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Extension/Geant4X/Memory/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::inline Simulation::inline Hit {

class EMCPMTHit final : public Mustard::Geant4X::UseG4Allocator<EMCPMTHit>,
                        public G4VHit,
                        public Mustard::Data::Tuple<Data::EMCPMTHit> {};

using EMCPMTHitCollection = G4THitsCollection<EMCPMTHit>;

} // namespace MACE::inline Simulation::inline Hit
