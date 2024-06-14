#pragma once

#include "MACE/Data/SensorHit.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Extension/Geant4X/Memory/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::inline Simulation::inline Hit {

class EMCPMTHit final : public Geant4X::UseG4Allocator<EMCPMTHit>,
                        public G4VHit,
                        public Data::Tuple<Data::EMCPMTHit> {};

using EMCPMTHitCollection = G4THitsCollection<EMCPMTHit>;

} // namespace MACE::inline Simulation::inline Hit
