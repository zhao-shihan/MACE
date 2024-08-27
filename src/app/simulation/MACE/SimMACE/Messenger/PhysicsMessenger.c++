#include "MACE/SimMACE/Messenger/PhysicsMessenger.h++"
#include "MACE/SimMACE/PhysicsList.h++"

#include "G4UIcmdWithABool.hh"

namespace MACE::SimMACE::inline Messenger {

PhysicsMessenger::PhysicsMessenger() :
    SingletonMessenger{},
    fApplyMACEPxyCut{} {

    fApplyMACEPxyCut = std::make_unique<G4UIcmdWithABool>("/MACE/Physics/MuonDecay/IPPDecay/ApplyMACEPxyCut", this);
    fApplyMACEPxyCut->SetGuidance("If true, apply MACE specific transverse momentum cut to mu+ IPP decay products. Check source code for details.");
    fApplyMACEPxyCut->SetParameterName("apply", false);
    fApplyMACEPxyCut->AvailableForStates(G4State_Idle);
}

PhysicsMessenger::~PhysicsMessenger() = default;

auto PhysicsMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fApplyMACEPxyCut.get()) {
        Deliver<PhysicsList>([&](auto&& r) {
            r.ApplyMACEPxyCut(fApplyMACEPxyCut->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::SimMACE::inline Messenger
