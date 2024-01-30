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

auto MuoniumPrecisionDecayPhysics::ConstructParticle() -> void {
    Muonium::Definition();
    Antimuonium::Definition();
}

auto MuoniumPrecisionDecayPhysics::ConstructProcess() -> void {
    const auto NewDecayTableFor{
        [this](G4ParticleDefinition* muonium) {
            const auto decay{new G4DecayTable};
            // ! sort by initial BR
            decay->Insert(new MuoniumDecayChannel{muonium->GetParticleName(), 1, verboseLevel});
            decay->Insert(new MuoniumInternalPairProductionDecayChannel{muonium->GetParticleName(), fIPPDecayBR, verboseLevel});
            CheckAndSetMainChannelBR(decay);
            delete muonium->GetDecayTable();
            muonium->SetDecayTable(decay);
        }};
    NewDecayTableFor(Muonium::Definition());
    NewDecayTableFor(Antimuonium::Definition());
    fProcessConstructed = true;
}

} // namespace MACE::inline Simulation::inline Physics
