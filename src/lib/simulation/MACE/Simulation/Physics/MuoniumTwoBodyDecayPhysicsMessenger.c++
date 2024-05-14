#include "MACE/Simulation/Physics/MuoniumTwoBodyDecayPhysics.h++"
#include "MACE/Simulation/Physics/MuoniumTwoBodyDecayPhysicsMessenger.h++"

#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Simulation::inline Physics {

MuoniumTwoBodyDecayPhysicsMessenger::MuoniumTwoBodyDecayPhysicsMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fAnnihilationBR{},
    fTwoBodyDecayBR{},
    fUpdateDecayBR{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Physics/MuoniumDecay/");
    fDirectory->SetGuidance("About muon(ium) decay channel and decay generators.");

    fAnnihilationBR = std::make_unique<G4UIcmdWithADouble>("/MACE/Physics/MuoniumDecay/Annihilation/BR", this);
    fAnnihilationBR->SetGuidance("Set branching ratio for muonium annihilation decay channel.");
    fAnnihilationBR->SetParameterName("BR", false);
    fAnnihilationBR->SetRange("0 <= BR && BR <= 1");
    fAnnihilationBR->AvailableForStates(G4State_PreInit, G4State_Idle);

    fTwoBodyDecayBR = std::make_unique<G4UIcmdWithADouble>("/MACE/Physics/MuoniumDecay/TwoBodyDecay/BR", this);
    fTwoBodyDecayBR->SetGuidance("Set branching ratio for muonium two-body decay channel.");
    fTwoBodyDecayBR->SetParameterName("BR", false);
    fTwoBodyDecayBR->SetRange("0 <= BR && BR <= 1");
    fTwoBodyDecayBR->AvailableForStates(G4State_PreInit, G4State_Idle);

    fUpdateDecayBR = std::make_unique<G4UIcmdWithoutParameter>("/MACE/Physics/MuoniumDecay/UpdateDecayBR", this);
    fUpdateDecayBR->SetGuidance("Update decay branching ratio.");
    fUpdateDecayBR->AvailableForStates(G4State_Idle);
}

auto MuoniumTwoBodyDecayPhysicsMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fAnnihilationBR.get()) {
        Deliver<MuoniumTwoBodyDecayPhysics>([&](auto&& r) {
            r.AnnihilationBR(fAnnihilationBR->GetNewDoubleValue(value));
        });
    } else if (command == fTwoBodyDecayBR.get()) {
        Deliver<MuoniumTwoBodyDecayPhysics>([&](auto&& r) {
            r.TwoBodyDecayBR(fTwoBodyDecayBR->GetNewDoubleValue(value));
        });
    } else if (command == fUpdateDecayBR.get()) {
        Deliver<MuoniumTwoBodyDecayPhysics>([&](auto&& r) {
            r.UpdateDecayBR();
        });
    }
}

} // namespace MACE::inline Simulation::inline Physics
