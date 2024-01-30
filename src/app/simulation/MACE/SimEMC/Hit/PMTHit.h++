#pragma once

#include "MACE/Data/SimHit.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::SimEMC::inline Hit {

class PMTHit final : public Geant4X::UseG4Allocator<PMTHit>,
                     public G4VHit,
                     public Data::Tuple<Data::PMTSimHit> {};

using PMTHitCollection = G4THitsCollection<PMTHit>;

} // namespace MACE::SimEMC::inline Hit
