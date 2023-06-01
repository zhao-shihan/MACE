#include "MACE/Compatibility/std2b/to_underlying.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/Extension/Geant4X/Physics/MuoniumPhysics.h++"
#include "MACE/SimTarget/PhysicsList.h++"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

namespace MACE::SimTarget {

using namespace MACE::Geant4X::Physics;

PhysicsList::PhysicsList() :
    PassiveSingleton(),
    G4VModularPhysicsList() {
    verboseLevel = std2b::to_underlying(Env::BasicEnv::Instance().GetVerboseLevel());
    RegisterPhysics(new G4EmStandardPhysics_option4(verboseLevel));
    RegisterPhysics(new MuoniumPhysics<Detector::Description::Target>(verboseLevel));
}

} // namespace MACE::SimTarget
