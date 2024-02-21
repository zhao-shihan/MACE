#include "MACE/Simulation/Physics/DecayChannel/MuoniumDecayChannel.h++"
#include "MACE/Simulation/Physics/DecayChannel/MuoniumInternalPairProductionDecayChannel.h++"
#include "MACE/Simulation/Physics/MuoniumPrecisionDecayPhysics.h++"
#include "MACE/Simulation/Physics/Particle/Antimuonium.h++"
#include "MACE/Simulation/Physics/Particle/Muonium.h++"

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
            decay->Insert(new MuoniumDecayChannel{muonium->GetParticleName(), 1e-1, verboseLevel});
            decay->Insert(new MuoniumInternalPairProductionDecayChannel{muonium->GetParticleName(), 1e-2, verboseLevel});
            // delete old table and set new
            delete muonium->GetDecayTable();
            muonium->SetDecayTable(decay);
        }};
    NewDecayTableFor(Muonium::Definition());
    NewDecayTableFor(Antimuonium::Definition());
    fDecayTableConstructed = true;
    // set BR here
    UpdateBR();
}

auto MuoniumPrecisionDecayPhysics::UpdateBR() -> void {
    UpdateBRFor(Muonium::Definition());
    UpdateBRFor(Antimuonium::Definition());
}

} // namespace MACE::inline Simulation::inline Physics
