#include "MACE/SimPTS/PhysicsList.h++"

#include "Mustard/Extension/Geant4X/DecayChannel/MuonInternalPairProductionDecayChannel.h++"
#include "Mustard/Extension/Geant4X/DecayChannel/MuoniumInternalPairProductionDecayChannel.h++"
#include "Mustard/Extension/Geant4X/Particle/Antimuonium.h++"
#include "Mustard/Extension/Geant4X/Particle/Muonium.h++"
#include "Mustard/Extension/Geant4X/Physics/MuoniumPrecisionDecayPhysics.h++"

#include "G4DecayTable.hh"
#include "G4MuonPlus.hh"

#include "fmt/core.h"

#include <stdexcept>
#include <typeinfo>

namespace MACE::SimPTS {

PhysicsList::PhysicsList() :
    PassiveSingleton<PhysicsList>{},
    StandardPhysicsListBase{} {}

} // namespace MACE::SimPTS
