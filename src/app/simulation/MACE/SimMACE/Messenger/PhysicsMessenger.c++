#include "MACE/SimMACE/Messenger/PhysicsMessenger.h++"
#include "MACE/SimMACE/PhysicsList.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

namespace MACE::SimMACE::inline Messenger {

PhysicsMessenger::PhysicsMessenger() :
    SingletonMessenger{},
    fApplyProductionCutNearTarget{},
    fMACECutMaxLowerPositronEk{},
    fApplyMACECut{} {

    fApplyProductionCutNearTarget = std::make_unique<G4UIcmdWithABool>("/MACE/Physics/ApplyProductionCutNearTarget", this);
    fApplyProductionCutNearTarget->SetGuidance("If yes, apply default production cut to the material-to-vacuum region near the target");
    fApplyProductionCutNearTarget->SetParameterName("apply", false);
    fApplyProductionCutNearTarget->AvailableForStates(G4State_Idle);

    fMACECutMaxLowerPositronEk = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Physics/MuonDecay/ICDecay/MACECutMaxLowerPositronEk", this);
    fMACECutMaxLowerPositronEk->SetGuidance("Set kinetic energy upper bound for e+ with lower kinetic energy.");
    fMACECutMaxLowerPositronEk->SetParameterName("Ek", false);
    fMACECutMaxLowerPositronEk->SetUnitCategory("Energy");
    fMACECutMaxLowerPositronEk->AvailableForStates(G4State_Idle);

    fApplyMACECut = std::make_unique<G4UIcmdWithABool>("/MACE/Physics/MuonDecay/ICDecay/ApplyMACECut", this);
    fApplyMACECut->SetGuidance("If yes, apply MACE specific transverse momentum cut to mu+ IPP decay products. Check source code for details.");
    fApplyMACECut->SetParameterName("apply", false);
    fApplyMACECut->AvailableForStates(G4State_Idle);
}

PhysicsMessenger::~PhysicsMessenger() = default;

auto PhysicsMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fApplyProductionCutNearTarget.get()) {
        Deliver<DetectorConstruction>([&](auto&& r) {
            r.ApplyProductionCutNearTarget(fApplyProductionCutNearTarget->GetNewBoolValue(value));
        });
    } else if (command == fMACECutMaxLowerPositronEk.get()) {
        Deliver<PhysicsList>([&](auto&& r) {
            r.MACECutMaxLowerPositronEk(fMACECutMaxLowerPositronEk->GetNewDoubleValue(value));
        });
    } else if (command == fApplyMACECut.get()) {
        Deliver<PhysicsList>([&](auto&& r) {
            r.ApplyMACECut(fApplyMACECut->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::SimMACE::inline Messenger
