#include "MACE/Extension/Geant4X/Antimuonium.h++"
#include "MACE/Extension/Geant4X/Muonium.h++"
#include "MACE/Extension/Geant4X/MuoniumDecayChannelWithSpin.h++"
#include "MACE/Extension/Geant4X/MuoniumRadiativeDecayChannelWithSpin.h++"
#include "MACE/Simulation/Physics/DecayChannel/MuoniumInternalPairProductionDecayChannel.h++"
#include "MACE/Simulation/Physics/MuoniumPrecisionDecayPhysics.h++"

#include "G4DecayTable.hh"
#include "G4DecayWithSpin.hh"
#include "G4EmBuilder.hh"
#include "G4ProcessTable.hh"

namespace MACE::inline Simulation::inline Physics {

MuoniumPrecisionDecayPhysics::MuoniumPrecisionDecayPhysics(G4int verbose) :
    MuonPrecisionDecayPhysics{verbose} {
    namePhysics = "MuoniumPrecisionDecayPhysics";
}

auto MuoniumPrecisionDecayPhysics::ConstructParticle() -> void {
    G4EmBuilder::ConstructMinimalEmSet();

    const auto NewDecayTableFor{
        [this](G4ParticleDefinition* muonium) {
            const auto decay{new G4DecayTable};
            InsertDecayChannel(muonium->GetParticleName(), decay);
            delete muonium->GetDecayTable();
            muonium->SetDecayTable(decay);
        }};
    NewDecayTableFor(Geant4X::Muonium::Definition());
    NewDecayTableFor(Geant4X::Antimuonium::Definition());

    UpdateDecayBR(); // set BR here
}

auto MuoniumPrecisionDecayPhysics::ConstructProcess() -> void {
    const auto ReplaceDecayPhysics{
        [decayWithSpin = new G4DecayWithSpin,
         processTable = G4ProcessTable::GetProcessTable()](G4ParticleDefinition* muonium) {
            const auto manager{muonium->GetProcessManager()};
            if (manager == nullptr) { return; }
            const auto decay{processTable->FindProcess("Decay", muonium)};
            if (decay) { manager->RemoveProcess(decay); }
            manager->AddProcess(decayWithSpin);
            // set ordering for PostStepDoIt and AtRestDoIt
            manager->SetProcessOrdering(decayWithSpin, idxPostStep);
            manager->SetProcessOrdering(decayWithSpin, idxAtRest);
        }};
    ReplaceDecayPhysics(Geant4X::Muonium::Definition());
    ReplaceDecayPhysics(Geant4X::Antimuonium::Definition());
}

auto MuoniumPrecisionDecayPhysics::UpdateDecayBR() -> void {
    UpdateDecayBRFor(Geant4X::Muonium::Definition());
    UpdateDecayBRFor(Geant4X::Antimuonium::Definition());
}

auto MuoniumPrecisionDecayPhysics::InsertDecayChannel(const G4String& parentName, gsl::not_null<G4DecayTable*> decay) -> void {
    // sort by initial BR! we firstly write random BRs in decrease order...
    decay->Insert(new Geant4X::MuoniumDecayChannelWithSpin{parentName, 1e-1, verboseLevel});
    decay->Insert(new Geant4X::MuoniumRadiativeDecayChannelWithSpin{parentName, 1e-2, verboseLevel});
    decay->Insert(new MuoniumInternalPairProductionDecayChannel{parentName, 1e-3, verboseLevel});
}

auto MuoniumPrecisionDecayPhysics::AssignRareDecayBR(gsl::not_null<G4DecayTable*> decay) -> void {
    // set BR here
    decay->GetDecayChannel(1)->SetBR(fRadiativeDecayBR);
    decay->GetDecayChannel(2)->SetBR(fIPPDecayBR);
}

} // namespace MACE::inline Simulation::inline Physics
