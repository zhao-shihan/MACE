#include "MACE/Math/Clamp.h++"
#include "MACE/Simulation/Physics/DecayChannel/MuonInternalPairProductionDecayChannel.h++"
#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysics.h++"

#include "G4DecayTable.hh"
#include "G4MuonDecayChannel.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"

#include <stdexcept>

namespace MACE::inline Simulation::inline Physics {

MuonPrecisionDecayPhysics::MuonPrecisionDecayPhysics(G4int verbose) :
    NonMoveableBase{},
    G4VPhysicsConstructor{"MuonPrecisionDecayPhysics"},
    fIPPDecayBR{3.4e-5},
    fDecayTableConstructed{},
    fMessengerRegister{this} {
    verboseLevel = verbose;
}

auto MuonPrecisionDecayPhysics::IPPDecayBR(double br) -> void {
    fIPPDecayBR = Math::Clamp<"[]">(br, 0., 1.);
    UpdateBR();
}

auto MuonPrecisionDecayPhysics::ConstructProcess() -> void {
    const auto NewDecayTableFor{
        [this](G4ParticleDefinition* muon) {
            const auto decay{new G4DecayTable};
            // sort by initial BR! we firstly write random BRs in decrease order...
            decay->Insert(new G4MuonDecayChannel{muon->GetParticleName(), 1e-1}), decay->GetDecayChannel(0)->SetVerboseLevel(verboseLevel);
            decay->Insert(new MuonInternalPairProductionDecayChannel{muon->GetParticleName(), 1e-2, verboseLevel});
            // delete old table and set new
            delete muon->GetDecayTable();
            muon->SetDecayTable(decay);
        }};
    NewDecayTableFor(G4MuonPlus::Definition());
    NewDecayTableFor(G4MuonMinus::Definition());
    fDecayTableConstructed = true;
    // set BR here
    UpdateBR();
}

auto MuonPrecisionDecayPhysics::UpdateBR() -> void {
    UpdateBRFor(G4MuonPlus::Definition());
    UpdateBRFor(G4MuonMinus::Definition());
}

auto MuonPrecisionDecayPhysics::UpdateBRFor(const G4ParticleDefinition* mu) -> void {
    if (not fDecayTableConstructed) { return; }
    const auto decay{mu->GetDecayTable()};
    // set rare decay mode first
    decay->GetDecayChannel(1)->SetBR(fIPPDecayBR);
    // then set main decay mode
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
