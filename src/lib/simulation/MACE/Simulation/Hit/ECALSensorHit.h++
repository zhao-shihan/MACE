#pragma once

#include "MACE/Data/SensorHit.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Extension/Geant4X/Memory/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::inline Simulation::inline Hit {

class ECALSensorHit final : public Mustard::Geant4X::UseG4Allocator<ECALSensorHit>,
                        public G4VHit,
                        public Mustard::Data::Tuple<Data::ECALSensorHit> {};

using ECALSensorHitCollection = G4THitsCollection<ECALSensorHit>;

} // namespace MACE::inline Simulation::inline Hit
