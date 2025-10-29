#pragma once

#include "MACE/PhaseI/Data/SensorHit.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Geant4X/Memory/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::PhaseI::inline Simulation::inline Hit {

class SciFiSiPMHit final : public Mustard::Geant4X::UseG4Allocator<SciFiSiPMHit>,
                           public G4VHit,
                           public Mustard::Data::Tuple<PhaseI::Data::SciFiSiPMHit> {};

using SciFiSiPMHitCollection = G4THitsCollection<SciFiSiPMHit>;

} // namespace MACE::PhaseI::inline Simulation::inline Hit
