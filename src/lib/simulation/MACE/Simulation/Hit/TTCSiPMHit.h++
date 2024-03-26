#pragma once

#include "MACE/Data/SimHit.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::inline Simulation::inline Hit {

class TTCSiPMHit final : public Geant4X::UseG4Allocator<TTCSiPMHit>,
                         public G4VHit,
                         public Data::Tuple<Data::TTCSiPMHit> {};

using TTCSiPMHitCollection = G4THitsCollection<TTCSiPMHit>;

} // namespace MACE::inline Simulation::inline Hit
