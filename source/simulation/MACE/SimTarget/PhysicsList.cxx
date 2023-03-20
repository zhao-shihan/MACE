#include "MACE/Compatibility/std2b/to_underlying.hxx"
#include "MACE/Detector/Description/Target.hxx"
#include "MACE/Env/BasicEnv.hxx"
#include "MACE/Extension/Geant4X/Physics/MuoniumPhysics.hxx"
#include "MACE/SimTarget/PhysicsList.hxx"

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
