#pragma once

#include "MACE/Data/SimHit.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::SimEMC::inline Hit {

class EMCHit final : public Geant4X::UseG4Allocator<EMCHit>,
                     public G4VHit,
                     public Data::Tuple<Data::EMCSimHit> {};

using EMCHitCollection = G4THitsCollection<EMCHit>;

} // namespace MACE::SimEMC::inline Hit
