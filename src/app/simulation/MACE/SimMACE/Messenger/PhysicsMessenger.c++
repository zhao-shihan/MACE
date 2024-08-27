#include "MACE/SimMACE/Messenger/PhysicsMessenger.h++"
#include "MACE/SimMACE/PhysicsList.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

namespace MACE::SimMACE::inline Messenger {

PhysicsMessenger::PhysicsMessenger() :
    SingletonMessenger{},
    fApplyProductionCutNearTarget{},
    fMACEPxyCutMaxLowerPositronEk{},
    fApplyMACEPxyCut{} {

    fApplyProductionCutNearTarget = std::make_unique<G4UIcmdWithABool>("/MACE/Physics/ApplyProductionCutNearTarget", this);
    fApplyProductionCutNearTarget->SetGuidance("If yes, apply default production cut to the material-to-vacuum region near the target");
    fApplyProductionCutNearTarget->SetParameterName("apply", false);
    fApplyProductionCutNearTarget->AvailableForStates(G4State_Idle);

    fMACEPxyCutMaxLowerPositronEk = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Physics/MuonDecay/ICDecay/MACEPxyCutMaxLowerPositronEk", this);
    fMACEPxyCutMaxLowerPositronEk->SetGuidance("Set kinetic energy upper bound for e+ with lower kinetic energy.");
    fMACEPxyCutMaxLowerPositronEk->SetParameterName("Ek", false);
    fMACEPxyCutMaxLowerPositronEk->SetUnitCategory("Energy");
    fMACEPxyCutMaxLowerPositronEk->AvailableForStates(G4State_Idle);

    fApplyMACEPxyCut = std::make_unique<G4UIcmdWithABool>("/MACE/Physics/MuonDecay/ICDecay/ApplyMACEPxyCut", this);
    fApplyMACEPxyCut->SetGuidance("If yes, apply MACE specific transverse momentum cut to mu+ IPP decay products. Check source code for details.");
    fApplyMACEPxyCut->SetParameterName("apply", false);
    fApplyMACEPxyCut->AvailableForStates(G4State_Idle);
}

PhysicsMessenger::~PhysicsMessenger() = default;

auto PhysicsMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fApplyProductionCutNearTarget.get()) {
        Deliver<DetectorConstruction>([&](auto&& r) {
            r.ApplyProductionCutNearTarget(fApplyProductionCutNearTarget->GetNewBoolValue(value));
        });
    } else if (command == fMACEPxyCutMaxLowerPositronEk.get()) {
        Deliver<PhysicsList>([&](auto&& r) {
            r.MACEPxyCutMaxLowerPositronEk(fMACEPxyCutMaxLowerPositronEk->GetNewDoubleValue(value));
        });
    } else if (command == fApplyMACEPxyCut.get()) {
        Deliver<PhysicsList>([&](auto&& r) {
            r.ApplyMACEPxyCut(fApplyMACEPxyCut->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::SimMACE::inline Messenger
