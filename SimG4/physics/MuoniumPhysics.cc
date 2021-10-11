#include "G4MuonPlus.hh"
#include "G4ProcessManager.hh"

#include "SimG4/physics/MuoniumPhysics.hh"
#include "SimG4/physics/AntiMuonium.hh"
#include "SimG4/physics/Muonium.hh"
// #include "physics/MuoniumLFV.hh"
#include "SimG4/physics/MuoniumProduction.hh"
#include "SimG4/physics/MuoniumTransport.hh"

using namespace MACE::SimG4::Physics;

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
    // muonium->AddDiscreteProcess(new MuoniumLFV());

    auto antiMuonium = AntiMuonium::Definition()->GetProcessManager();
    antiMuonium->AddContinuousProcess(muoniumTransport);
}
