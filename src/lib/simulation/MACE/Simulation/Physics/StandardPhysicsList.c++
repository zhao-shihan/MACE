#include "MACE/Detector/Description/Target.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysics.h++"
#include "MACE/Simulation/Physics/MuoniumPhysics.h++"
#include "MACE/Simulation/Physics/MuoniumPrecisionDecayPhysics.h++"
#include "MACE/Simulation/Physics/MuoniumTwoBodyDecayPhysics.h++"
#include "MACE/Simulation/Physics/StandardPhysicsList.h++"

#include "G4EmStandardPhysics_option4.hh"
#include "G4SpinDecayPhysics.hh"

#include "muc/utility"

#include <algorithm>

namespace MACE::inline Simulation::inline Physics {

StandardPhysicsListBase::StandardPhysicsListBase() :
    FTFP_BERT{std::max({}, muc::to_underlying(Env::BasicEnv::Instance().VerboseLevel()))} {
    // EMZ
    ReplacePhysics(new G4EmStandardPhysics_option4{verboseLevel});
    // Muonium physics
    RegisterPhysics(new MuoniumPhysics<Detector::Description::Target>{verboseLevel});
    // HP decay for muon and muonium
    ReplacePhysics(new G4SpinDecayPhysics{verboseLevel});
    RegisterPhysics(new MuonPrecisionDecayPhysics{verboseLevel});
    RegisterPhysics(new MuoniumPrecisionDecayPhysics{verboseLevel});
    RegisterPhysics(new MuoniumTwoBodyDecayPhysics{verboseLevel});
}

} // namespace MACE::inline Simulation::inline Physics
