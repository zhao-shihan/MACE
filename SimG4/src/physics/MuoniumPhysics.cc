#include "G4MuonPlus.hh"
#include "G4ProcessManager.hh"

#include "physics/MuoniumPhysics.hh"
#include "physics/AntiMuonium.hh"
#include "physics/Muonium.hh"
#include "physics/MuoniumProduction.hh"

using namespace MACE::SimG4::Physics;

MuoniumPhysics::MuoniumPhysics(G4int verbose) :
    G4VPhysicsConstructor("MuoniumPhysics"),
    fVerbose(verbose) {}

void MuoniumPhysics::ConstructParticle() {
    G4MuonPlus::Definition();
    Muonium::Definition();
}

void MuoniumPhysics::ConstructProcess() {
    auto muonPlus = G4MuonPlus::Definition()->GetProcessManager();
    // auto muonium = Muonium::Definition()->GetProcessManager();

    muonPlus->AddRestProcess(new MuoniumProduction());
    // muonium->AddProcess()
}
