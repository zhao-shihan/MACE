#include "MACE/SimulationG4/Physics/MuoniumPhysics.hxx"
#include "MACE/SimulationG4/Physics/Particle/AntiMuonium.hxx"
#include "MACE/SimulationG4/Physics/Particle/Muonium.hxx"
#include "MACE/SimulationG4/Physics/Process/MuoniumFormation.hxx"
#include "MACE/SimulationG4/Physics/Process/MuoniumTransport.hxx"

#include "G4MuonPlus.hh"
#include "G4ProcessManager.hh"

namespace MACE::SimulationG4::Physics {

using namespace Particle;
using namespace Process;

MuoniumPhysics::MuoniumPhysics(G4int verbose) :
    G4VPhysicsConstructor("MuoniumPhysics") {
    SetVerboseLevel(verbose);
}

void MuoniumPhysics::ConstructParticle() {
    G4MuonPlus::Definition();
    Muonium::Definition();
    AntiMuonium::Definition();
}

void MuoniumPhysics::ConstructProcess() {
    auto muoniumFormation = new MuoniumFormation();
    auto muoniumTransport = new MuoniumTransport();

    auto muonPlus = G4MuonPlus::Definition()->GetProcessManager();
    muonPlus->AddRestProcess(muoniumFormation);

    auto muonium = Muonium::Definition()->GetProcessManager();
    muonium->AddContinuousProcess(muoniumTransport);

    auto antiMuonium = AntiMuonium::Definition()->GetProcessManager();
    antiMuonium->AddContinuousProcess(muoniumTransport);
}

} // namespace MACE::SimulationG4::Physics
