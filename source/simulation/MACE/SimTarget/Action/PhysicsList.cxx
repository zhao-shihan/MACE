#include "MACE/SimTarget/Action/PhysicsList.hxx"
#include "MACE/SimulationG4/Physics/MuoniumPhysics.hxx"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

namespace MACE::SimTarget::Action {

using namespace MACE::SimulationG4::Physics;

PhysicsList::PhysicsList() :
    NonCopyableBase(),
    G4VModularPhysicsList() {
    constexpr G4int defaultVerbose = 0;
    SetVerboseLevel(defaultVerbose);
    RegisterPhysics(new G4EmStandardPhysics_option4(defaultVerbose));
    RegisterPhysics(new G4DecayPhysics(defaultVerbose));
    RegisterPhysics(new MuoniumPhysics(defaultVerbose));
}

} // namespace MACE::SimTarget::Action
