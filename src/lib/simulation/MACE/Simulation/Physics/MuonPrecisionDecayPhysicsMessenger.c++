#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysics.h++"
#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysicsMessenger.h++"

#include "G4UIcmdWithADouble.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Simulation::inline Physics {

MuonPrecisionDecayPhysicsMessenger::MuonPrecisionDecayPhysicsMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fIPPDecayBR{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Physics/MuonDecay/");
    fDirectory->SetGuidance("About muon(ium) decay channel and decay generators.");

    fIPPDecayBR = std::make_unique<G4UIcmdWithADouble>("/MACE/Physics/MuonDecay/IPPDecay/BR", this);
    fIPPDecayBR->SetGuidance("Set branching ratio for muon(ium) internal pair production decay channel.");
    fIPPDecayBR->SetParameterName("BR", false);
    fIPPDecayBR->SetRange("0 <= BR && BR <= 1");
    fIPPDecayBR->AvailableForStates(G4State_PreInit, G4State_Idle);
}

MuonPrecisionDecayPhysicsMessenger::~MuonPrecisionDecayPhysicsMessenger() = default;

auto MuonPrecisionDecayPhysicsMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fIPPDecayBR.get()) {
        Deliver<MuonPrecisionDecayPhysics>([&](auto&& r) {
            r.IPPDecayBR(fIPPDecayBR->GetNewDoubleValue(value));
        });
    }
}

} // namespace MACE::inline Simulation::inline Physics
