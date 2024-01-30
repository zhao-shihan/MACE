#pragma once

#include "MACE/Data/SimHit.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::Simulation::inline Hit {

class EMCPMTHit final : public Geant4X::UseG4Allocator<EMCPMTHit>,
                        public G4VHit,
                        public Data::Tuple<Data::EMCPMTSimHit> {};

using EMCPMTHitCollection = G4THitsCollection<EMCPMTHit>;

} // namespace MACE::Simulation::inline Hit
