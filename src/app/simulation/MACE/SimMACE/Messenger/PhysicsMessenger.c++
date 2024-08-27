#include "MACE/SimMACE/Messenger/PhysicsMessenger.h++"
#include "MACE/SimMACE/PhysicsList.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

namespace MACE::SimMACE::inline Messenger {

PhysicsMessenger::PhysicsMessenger() :
    SingletonMessenger{},
    fMACEPxyCutMaxLowerPositronEk{},
    fApplyMACEPxyCut{} {

    fMACEPxyCutMaxLowerPositronEk = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Physics/MuonDecay/ICDecay/MACEPxyCutMaxLowerPositronEk", this);
    fMACEPxyCutMaxLowerPositronEk->SetGuidance("Set kinetic energy upper bound for e+ with lower kinetic energy.");
    fMACEPxyCutMaxLowerPositronEk->SetParameterName("Ek", false);
    fMACEPxyCutMaxLowerPositronEk->SetUnitCategory("Energy");
    fMACEPxyCutMaxLowerPositronEk->AvailableForStates(G4State_Idle);

    fApplyMACEPxyCut = std::make_unique<G4UIcmdWithABool>("/MACE/Physics/MuonDecay/ICDecay/ApplyMACEPxyCut", this);
    fApplyMACEPxyCut->SetGuidance("If true, apply MACE specific transverse momentum cut to mu+ IPP decay products. Check source code for details.");
    fApplyMACEPxyCut->SetParameterName("apply", false);
    fApplyMACEPxyCut->AvailableForStates(G4State_Idle);
}

PhysicsMessenger::~PhysicsMessenger() = default;

auto PhysicsMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fMACEPxyCutMaxLowerPositronEk.get()) {
        Deliver<PhysicsList>([&](auto&& r) {
            r.MACEPxyCutMaxLowerPositronEk(fMACEPxyCutMaxLowerPositronEk->GetNewDoubleValue(value));
        });
    }else if (command == fApplyMACEPxyCut.get()) {
        Deliver<PhysicsList>([&](auto&& r) {
            r.ApplyMACEPxyCut(fApplyMACEPxyCut->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::SimMACE::inline Messenger
