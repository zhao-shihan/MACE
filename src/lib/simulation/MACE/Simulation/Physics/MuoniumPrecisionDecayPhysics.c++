#include "MACE/Extension/Geant4X/Antimuonium.h++"
#include "MACE/Extension/Geant4X/Muonium.h++"
#include "MACE/Extension/Geant4X/MuoniumDecayChannelWithSpin.h++"
#include "MACE/Simulation/Physics/DecayChannel/MuoniumInternalPairProductionDecayChannel.h++"
#include "MACE/Simulation/Physics/MuoniumPrecisionDecayPhysics.h++"

#include "G4DecayTable.hh"

namespace MACE::inline Simulation::inline Physics {

MuoniumPrecisionDecayPhysics::MuoniumPrecisionDecayPhysics(G4int verbose) :
    MuonPrecisionDecayPhysics{verbose} {
    namePhysics = "MuoniumPrecisionDecayPhysics";
}

auto MuoniumPrecisionDecayPhysics::ConstructProcess() -> void {
    const auto NewDecayTableFor{
        [this](G4ParticleDefinition* muonium) {
            const auto decay{new G4DecayTable};
            // sort by initial BR! we firstly write random BRs in decrease order...
            decay->Insert(new Geant4X::MuoniumDecayChannelWithSpin{muonium->GetParticleName(), 1e-1, verboseLevel});
            decay->Insert(new MuoniumInternalPairProductionDecayChannel{muonium->GetParticleName(), 1e-2, verboseLevel});
            // delete old table and set new
            delete muonium->GetDecayTable();
            muonium->SetDecayTable(decay);
        }};
    NewDecayTableFor(Geant4X::Muonium::Definition());
    NewDecayTableFor(Geant4X::Antimuonium::Definition());
    fDecayTableConstructed = true;
    // set BR here
    UpdateBR();
}

auto MuoniumPrecisionDecayPhysics::UpdateBR() -> void {
    UpdateBRFor(Geant4X::Muonium::Definition());
    UpdateBRFor(Geant4X::Antimuonium::Definition());
}

} // namespace MACE::inline Simulation::inline Physics
