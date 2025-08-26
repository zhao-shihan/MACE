#pragma once

#include "MACE/PhaseI/Data/SimHit.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Extension/Geant4X/Memory/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::PhaseI::inline Simulation::inline Hit {

class TTCHit final : public Mustard::Geant4X::UseG4Allocator<TTCHit>,
                     public G4VHit,
                     public Mustard::Data::Tuple<PhaseI::Data::TTCSimHit> {};

using TTCHitCollection = G4THitsCollection<TTCHit>;

} // namespace MACE::PhaseI::inline Simulation::inline Hit
