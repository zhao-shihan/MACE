#include "MACE/Geant4X/Physics/MuoniumPhysics.hxx"
#include "MACE/Geant4X/Physics/Particle/AntiMuonium.hxx"
#include "MACE/Geant4X/Physics/Particle/Muonium.hxx"
#include "MACE/Geant4X/Physics/Process/MuoniumFormation.hxx"
#include "MACE/Geant4X/Physics/Process/MuoniumTransport.hxx"

#include "G4MuonPlus.hh"
#include "G4ProcessManager.hh"

namespace MACE::Geant4X::Physics {

using namespace Particle;
using namespace Process;

MuoniumPhysics::MuoniumPhysics(G4int verbose) :
    G4VPhysicsConstructor("MuoniumPhysics") {
    verboseLevel = verbose;
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

} // namespace MACE::Geant4X::Physics
