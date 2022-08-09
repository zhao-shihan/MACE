#include "MACE/Cxx2b/ToUnderlying.hxx"
#include "MACE/Environment/BasicEnvironment.hxx"
#include "MACE/Geant4X/Physics/MuoniumPhysics.hxx"
#include "MACE/SimTarget/Action/PhysicsList.hxx"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

namespace MACE::SimTarget::Action {

using namespace MACE::Geant4X::Physics;

PhysicsList::PhysicsList() :
    NonMoveableBase(),
    G4VModularPhysicsList() {
    verboseLevel = Cxx2b::ToUnderlying(Environment::BasicEnvironment::Instance().GetVerboseLevel());
    RegisterPhysics(new G4EmStandardPhysics_option4(verboseLevel));
    RegisterPhysics(new G4DecayPhysics(verboseLevel));
    RegisterPhysics(new MuoniumPhysics(verboseLevel));
}

} // namespace MACE::SimTarget::Action
