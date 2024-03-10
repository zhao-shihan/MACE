#include "MACE/Compatibility/std23/to_underlying.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/SimTarget/PhysicsList.h++"
#include "MACE/Simulation/Physics/MuoniumPhysics.h++"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

namespace MACE::SimTarget {

PhysicsList::PhysicsList() :
    PassiveSingleton{},
    G4VModularPhysicsList{} {
    verboseLevel = std23::to_underlying(Env::BasicEnv::Instance().VerboseLevel());
    RegisterPhysics(new G4EmStandardPhysics_option4(verboseLevel));
    RegisterPhysics(new G4DecayPhysics(verboseLevel));
    RegisterPhysics(new MuoniumPhysics<Detector::Description::Target>(verboseLevel));
}

} // namespace MACE::SimTarget
