#include "MACE/Simulation/Physics/MuoniumPhysics2.hxx"
#include "MACE/Simulation/Physics/Particle/AntiMuonium.hxx"
#include "MACE/Simulation/Physics/Particle/Muonium.hxx"
#include "MACE/Simulation/Physics/Process/MuoniumFormation.hxx"
#include "MACE/Simulation/Physics/Process/MuoniumTransport.hxx"

#include "G4MuonPlus.hh"
#include "G4ProcessManager.hh"

namespace MACE::Simulation::Physics {

using namespace Particle;
using namespace Process;

MuoniumPhysics2::MuoniumPhysics2(G4int verbose) :
    G4VPhysicsConstructor("MuoniumPhysics2"),
    fVerbose(verbose) {}

void MuoniumPhysics2::ConstructParticle() {
    G4MuonPlus::Definition();
    Muonium::Definition();
    AntiMuonium::Definition();
}

void MuoniumPhysics2::ConstructProcess() {
    auto muoniumFormation = new MuoniumFormation();
    auto muoniumTransport = new MuoniumTransport();

    auto muonPlus = G4MuonPlus::Definition()->GetProcessManager();
    muonPlus->AddRestProcess(muoniumFormation);

    auto muonium = Muonium::Definition()->GetProcessManager();
    muonium->AddContinuousProcess(muoniumTransport);

    auto antiMuonium = AntiMuonium::Definition()->GetProcessManager();
    antiMuonium->AddContinuousProcess(muoniumTransport);
}

} // namespace MACE::Simulation::Physics
