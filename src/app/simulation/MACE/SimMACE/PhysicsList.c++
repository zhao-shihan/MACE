#include "MACE/Compatibility/std23/to_underlying.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/SimMACE/PhysicsList.h++"
#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysics.h++"
#include "MACE/Simulation/Physics/MuoniumPhysics.h++"
#include "MACE/Simulation/Physics/MuoniumPrecisionDecayPhysics.h++"

#include "G4EmStandardPhysics_option4.hh"

#include <stdexcept>

namespace MACE::SimMACE {

PhysicsList::PhysicsList() :
    PassiveSingleton{},
    FTFP_BERT{std23::to_underlying(Env::BasicEnv::Instance().VerboseLevel())} {
    // EMZ
    ReplacePhysics(new G4EmStandardPhysics_option4{verboseLevel});
    // Muonium physics
    RegisterPhysics(new MuoniumPhysics<Detector::Description::Target>{verboseLevel});
    // HP decay for muon and muonium
    RegisterPhysics(new MuonPrecisionDecayPhysics{verboseLevel});
    RegisterPhysics(new MuoniumPrecisionDecayPhysics{verboseLevel});
}

} // namespace MACE::SimMACE
