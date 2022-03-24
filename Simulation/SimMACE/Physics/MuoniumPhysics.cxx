#include "SimMACE/Physics/AntiMuonium.hxx"
#include "SimMACE/Physics/Muonium.hxx"
#include "SimMACE/Physics/MuoniumPhysics.hxx"
#include "SimMACE/Physics/MuoniumProduction.hxx"
#include "SimMACE/Physics/MuoniumTransport.hxx"

#include "G4MuonPlus.hh"
#include "G4ProcessManager.hh"

using MACE::Simulation::SimMACE::Physics::MuoniumPhysics;

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
