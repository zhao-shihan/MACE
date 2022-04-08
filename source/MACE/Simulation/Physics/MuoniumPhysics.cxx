#include "MACE/Simulation/Physics/AntiMuonium.hxx"
#include "MACE/Simulation/Physics/Muonium.hxx"
#include "MACE/Simulation/Physics/MuoniumPhysics.hxx"
#include "MACE/Simulation/Physics/MuoniumProduction.hxx"
#include "MACE/Simulation/Physics/MuoniumTransport.hxx"

#include "G4MuonPlus.hh"
#include "G4ProcessManager.hh"

using MACE::Simulation::Physics::MuoniumPhysics;

MuoniumPhysics::MuoniumPhysics(G4int verbose) :
    G4VPhysicsConstructor("MuoniumPhysics"),
    fVerbose(verbose) {}

void MuoniumPhysics::ConstructParticle() {
    G4MuonPlus::Definition();
    AntiMuonium::Definition();
    Muonium::Definition();
}

void MuoniumPhysics::ConstructProcess() {
    auto muoniumProduction = new MuoniumProduction();
    auto muoniumTransport = new MuoniumTransport();

    auto muonPlus = G4MuonPlus::Definition()->GetProcessManager();
    muonPlus->AddRestProcess(muoniumProduction);

    auto muonium = Muonium::Definition()->GetProcessManager();
    muonium->AddContinuousProcess(muoniumTransport);

    auto antiMuonium = AntiMuonium::Definition()->GetProcessManager();
    antiMuonium->AddContinuousProcess(muoniumTransport);
}
