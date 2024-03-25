#include "MACE/Compatibility/std23/to_underlying.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/SimMMS/PhysicsList.h++"
#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysics.h++"

#include "G4EmStandardPhysics_option4.hh"

#include <algorithm>

namespace MACE::SimMMS {

PhysicsList::PhysicsList() :
    PassiveSingleton{},
    FTFP_BERT{std::max({}, std23::to_underlying(Env::BasicEnv::Instance().VerboseLevel()))} {
    // EMZ
    ReplacePhysics(new G4EmStandardPhysics_option4{verboseLevel});
    // HP decay for muon
    RegisterPhysics(new MuonPrecisionDecayPhysics{verboseLevel});
}

} // namespace MACE::SimMMS
