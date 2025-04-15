#pragma once

#include "MACE/PhaseI/Data/SensorHit.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Extension/Geant4X/Memory/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::PhaseI::inline Simulation::inline Hit {

class ECALPMHit final : public Mustard::Geant4X::UseG4Allocator<ECALPMHit>,
                        public G4VHit,
                        public Mustard::Data::Tuple<PhaseI::Data::ECALPMHit> {};

using ECALPMHitCollection = G4THitsCollection<ECALPMHit>;

} // namespace MACE::PhaseI::inline Simulation::inline Hit
