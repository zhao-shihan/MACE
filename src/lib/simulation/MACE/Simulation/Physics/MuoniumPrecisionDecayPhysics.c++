#include "MACE/Simulation/Physics/DecayChannel/MuoniumDecayChannel.h++"
#include "MACE/Simulation/Physics/DecayChannel/MuoniumInternalPairProductionDecayChannel.h++"
#include "MACE/Simulation/Physics/MuoniumPrecisionDecayPhysics.h++"
#include "MACE/Simulation/Physics/Particle/Antimuonium.h++"
#include "MACE/Simulation/Physics/Particle/Muonium.h++"

#include "G4DecayTable.hh"

namespace MACE::inline Simulation::inline Physics {

MuoniumPrecisionDecayPhysics::MuoniumPrecisionDecayPhysics(G4int verbose) :
    NonMoveableBase{},
    G4VPhysicsConstructor{"MuoniumPrecisionDecayPhysics"} {
    verboseLevel = verbose;
}

auto MuoniumPrecisionDecayPhysics::ConstructParticle() -> void {
    Muonium::Definition();
    Antimuonium::Definition();
}

auto MuoniumPrecisionDecayPhysics::ConstructProcess() -> void {
    const auto NewDecayTableFor{
        [this](G4ParticleDefinition* muonium) {
            const auto decayTable{new G4DecayTable};
            decayTable->Insert(new MuoniumDecayChannel{muonium->GetParticleName(), 1 - fgMuonIPPDecayBR, verboseLevel});
            decayTable->Insert(new MuoniumInternalPairProductionDecayChannel{muonium->GetParticleName(), fgMuonIPPDecayBR, verboseLevel});
            delete muonium->GetDecayTable();
            muonium->SetDecayTable(decayTable);
        }};
    NewDecayTableFor(Muonium::Definition());
    NewDecayTableFor(Antimuonium::Definition());
}

} // namespace MACE::inline Simulation::inline Physics
