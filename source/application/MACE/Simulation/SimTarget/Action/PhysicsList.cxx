#include "MACE/Simulation/Physics/MuoniumPhysics.hxx"
#include "MACE/Simulation/SimTarget/Action/PhysicsList.hxx"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

namespace MACE::Simulation::SimTarget::Action {

using namespace MACE::Simulation::Physics;

PhysicsList::PhysicsList() :
    G4VModularPhysicsList() {
    constexpr G4int defaultVerbose = 0;
    SetVerboseLevel(defaultVerbose);
    RegisterPhysics(new G4EmStandardPhysics_option4(defaultVerbose));
    RegisterPhysics(new G4DecayPhysics(defaultVerbose));
    RegisterPhysics(new MuoniumPhysics(defaultVerbose));
}

} // namespace MACE::Simulation::SimTarget::Action
