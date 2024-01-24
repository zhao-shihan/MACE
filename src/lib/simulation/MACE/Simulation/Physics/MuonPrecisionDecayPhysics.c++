#include "MACE/Simulation/Physics/DecayChannel/MuonInternalPairProductionDecayChannel.h++"
#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysics.h++"

#include "G4DecayTable.hh"
#include "G4MuonDecayChannel.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"

#include <algorithm>
#include <stdexcept>

namespace MACE::inline Simulation::inline Physics {

MuonPrecisionDecayPhysics::MuonPrecisionDecayPhysics(G4int verbose) :
    NonMoveableBase{},
    G4VPhysicsConstructor{"MuonPrecisionDecayPhysics"},
    fProcessConstructed{},
    fIPPDecayBR{3.4e-5},
    fMessengerRegister{this} {
    verboseLevel = verbose;
}

auto MuonPrecisionDecayPhysics::IPPDecayBR(double br) -> void {
    fIPPDecayBR = std::clamp(br, 0., 1.);
    if (fProcessConstructed) {
        ConstructProcess();
    }
}

auto MuonPrecisionDecayPhysics::ConstructParticle() -> void {
    G4MuonPlus::Definition();
    G4MuonMinus::Definition();
}

auto MuonPrecisionDecayPhysics::ConstructProcess() -> void {
    const auto NewDecayTableFor{
        [this](G4ParticleDefinition* muon) {
            const auto decay{new G4DecayTable};
            // ! sort by initial BR
            decay->Insert(new G4MuonDecayChannel{muon->GetParticleName(), 1});
            decay->Insert(new MuonInternalPairProductionDecayChannel{muon->GetParticleName(), fIPPDecayBR, verboseLevel});
            decay->GetDecayChannel(0)->SetVerboseLevel(verboseLevel);
            CheckAndSetMainChannelBR(decay);
            delete muon->GetDecayTable();
            muon->SetDecayTable(decay);
        }};
    NewDecayTableFor(G4MuonPlus::Definition());
    NewDecayTableFor(G4MuonMinus::Definition());
    fProcessConstructed = true;
}

auto MuonPrecisionDecayPhysics::CheckAndSetMainChannelBR(const G4DecayTable* decay) -> void {
    double mainDecayBR{1};
    for (auto i{1}; i < decay->entries(); ++i) {
        mainDecayBR -= decay->GetDecayChannel(i)->GetBR();
    }
    if (mainDecayBR < 0) {
        decay->DumpInfo();
        throw std::runtime_error{"Impossible to normalize decay branching ratio (sum of rare channel BR > 1)"};
    }
    decay->GetDecayChannel(0)->SetBR(mainDecayBR);
}

} // namespace MACE::inline Simulation::inline Physics
