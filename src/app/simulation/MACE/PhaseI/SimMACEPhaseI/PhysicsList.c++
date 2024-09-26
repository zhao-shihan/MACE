#include "MACE/PhaseI/SimMACEPhaseI/PhysicsList.h++"

#include "Mustard/Extension/Geant4X/Physics/MuoniumSMAndLFVDecayPhysics.h++"

namespace MACE::PhaseI::SimMACEPhaseI {

PhysicsList::PhysicsList() :
    PassiveSingleton<PhysicsList>{},
    StandardPhysicsListBase{} {
    ReplacePhysics(new Mustard::Geant4X::MuoniumSMAndLFVDecayPhysics{verboseLevel});
}

} // namespace MACE::PhaseI::SimMACEPhaseI
