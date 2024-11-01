#include "MACE/SimMACE/Messenger/PhysicsMessenger.h++"
#include "MACE/SimMACE/PhysicsList.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

namespace MACE::SimMACE::inline Messenger {

PhysicsMessenger::PhysicsMessenger() :
    SingletonMessenger{},
    fApplyProductionCutNearTarget{},
    fMACEBiasPxySofteningFactor{},
    fMACEBiasCosSofteningFactor{},
    fMACEBiasEkLow{},
    fMACEBiasEkSofteningFactor{},
    fApplyMACEBias{} {

    fApplyProductionCutNearTarget = std::make_unique<G4UIcmdWithABool>("/MACE/Physics/ApplyProductionCutNearTarget", this);
    fApplyProductionCutNearTarget->SetGuidance("If yes, apply default production cut to the material-to-vacuum region near the target");
    fApplyProductionCutNearTarget->SetParameterName("apply", false);
    fApplyProductionCutNearTarget->AvailableForStates(G4State_Idle);

    fMACEBiasPxySofteningFactor = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Physics/MuonDecay/ICDecay/MACEBiasPxySofteningFactor", this);
    fMACEBiasPxySofteningFactor->SetGuidance("See source code for more details.");
    fMACEBiasPxySofteningFactor->SetParameterName("s_Pxy", false);
    fMACEBiasPxySofteningFactor->SetUnitCategory("Energy");
    fMACEBiasPxySofteningFactor->AvailableForStates(G4State_Idle);

    fMACEBiasCosSofteningFactor = std::make_unique<G4UIcmdWithADouble>("/MACE/Physics/MuonDecay/ICDecay/MACEBiasCosSofteningFactor", this);
    fMACEBiasCosSofteningFactor->SetGuidance("See source code for more details.");
    fMACEBiasCosSofteningFactor->SetParameterName("s_cos", false);
    fMACEBiasCosSofteningFactor->AvailableForStates(G4State_Idle);

    fMACEBiasEkLow = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Physics/MuonDecay/ICDecay/MACEBiasEkLow", this);
    fMACEBiasEkLow->SetGuidance("See source code for more details.");
    fMACEBiasEkLow->SetParameterName("Ek", false);
    fMACEBiasEkLow->SetUnitCategory("Energy");
    fMACEBiasEkLow->AvailableForStates(G4State_Idle);

    fMACEBiasEkSofteningFactor = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Physics/MuonDecay/ICDecay/MACEBiasEkSofteningFactor", this);
    fMACEBiasEkSofteningFactor->SetGuidance("See source code for more details.");
    fMACEBiasEkSofteningFactor->SetParameterName("s_Ek", false);
    fMACEBiasEkSofteningFactor->SetUnitCategory("Energy");
    fMACEBiasEkSofteningFactor->AvailableForStates(G4State_Idle);

    fApplyMACEBias = std::make_unique<G4UIcmdWithABool>("/MACE/Physics/MuonDecay/ICDecay/ApplyMACEBias", this);
    fApplyMACEBias->SetGuidance("If yes, apply MACE specific transverse momentum cut to mu+ IPP decay products. Check source code for details.");
    fApplyMACEBias->SetParameterName("apply", false);
    fApplyMACEBias->AvailableForStates(G4State_Idle);
}

PhysicsMessenger::~PhysicsMessenger() = default;

auto PhysicsMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fApplyProductionCutNearTarget.get()) {
        Deliver<DetectorConstruction>([&](auto&& r) {
            r.ApplyProductionCutNearTarget(fApplyProductionCutNearTarget->GetNewBoolValue(value));
        });
    } else if (command == fMACEBiasPxySofteningFactor.get()) {
        Deliver<PhysicsList>([&](auto&& r) {
            r.MACEBiasPxySofteningFactor(fMACEBiasPxySofteningFactor->GetNewDoubleValue(value));
        });
    } else if (command == fMACEBiasCosSofteningFactor.get()) {
        Deliver<PhysicsList>([&](auto&& r) {
            r.MACEBiasCosSofteningFactor(fMACEBiasCosSofteningFactor->GetNewDoubleValue(value));
        });
    } else if (command == fMACEBiasEkLow.get()) {
        Deliver<PhysicsList>([&](auto&& r) {
            r.MACEBiasEkLow(fMACEBiasEkLow->GetNewDoubleValue(value));
        });
    } else if (command == fMACEBiasEkSofteningFactor.get()) {
        Deliver<PhysicsList>([&](auto&& r) {
            r.MACEBiasEkSofteningFactor(fMACEBiasEkSofteningFactor->GetNewDoubleValue(value));
        });
    } else if (command == fApplyMACEBias.get()) {
        Deliver<PhysicsList>([&](auto&& r) {
            r.ApplyMACEBias(fApplyMACEBias->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::SimMACE::inline Messenger
