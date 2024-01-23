#include "MACE/Compatibility/std23/to_underlying.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/SimMACE/PhysicsList.h++"
#include "MACE/Simulation/Physics/MuoniumPhysics.h++"

#include "G4EmStandardPhysics_option4.hh"

#include <stdexcept>

namespace MACE::SimMACE {

using namespace MACE::LiteralUnit::Length;

PhysicsList::PhysicsList() :
    PassiveSingleton{},
    FTFP_BERT{std23::to_underlying(Env::BasicEnv::Instance().GetVerboseLevel())} {
    // EMZ
    ReplacePhysics(new G4EmStandardPhysics_option4{verboseLevel});
    // Muonium physics
    RegisterPhysics(new MuoniumPhysics<Detector::Description::Target>{verboseLevel});
}

} // namespace MACE::SimMACE
