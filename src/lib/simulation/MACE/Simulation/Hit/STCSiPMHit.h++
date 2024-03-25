#pragma once

#include "MACE/Data/SimHit.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::inline Simulation::inline Hit {

class STCSiPMHit final : public Geant4X::UseG4Allocator<STCSiPMHit>,
                         public G4VHit,
                         public Data::Tuple<Data::STCSiPMSimHit> {};

using STCSiPMHitCollection = G4THitsCollection<STCSiPMHit>;

} // namespace MACE::inline Simulation::inline Hit
