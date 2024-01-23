#include "MACE/Simulation/Physics/DecayChannel/MuonInternalPairProductionDecayChannel.h++"
#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysics.h++"

#include "G4DecayTable.hh"
#include "G4MuonDecayChannel.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"

namespace MACE::inline Simulation::inline Physics {

MuonPrecisionDecayPhysics::MuonPrecisionDecayPhysics(G4int verbose) :
    NonMoveableBase{},
    G4VPhysicsConstructor{"MuonPrecisionDecayPhysics"} {
    verboseLevel = verbose;
}

auto MuonPrecisionDecayPhysics::ConstructParticle() -> void {
    G4MuonPlus::Definition();
    G4MuonMinus::Definition();
}

auto MuonPrecisionDecayPhysics::ConstructProcess() -> void {
    const auto NewDecayTableFor{
        [this](G4ParticleDefinition* muon) {
            const auto decayTable{new G4DecayTable};
            decayTable->Insert(new G4MuonDecayChannel{muon->GetParticleName(), 1 - fgMuonIPPDecayBR});
            decayTable->Insert(new MuonInternalPairProductionDecayChannel{muon->GetParticleName(), fgMuonIPPDecayBR, verboseLevel});
            decayTable->GetDecayChannel(0)->SetVerboseLevel(verboseLevel);
            delete muon->GetDecayTable();
            muon->SetDecayTable(decayTable);
        }};
    NewDecayTableFor(G4MuonPlus::Definition());
    NewDecayTableFor(G4MuonMinus::Definition());
}

} // namespace MACE::inline Simulation::inline Physics
