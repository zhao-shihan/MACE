#include "MACE/Extension/Geant4X/GeneralParticleSourceX.h++"
#include "MACE/Extension/Geant4X/GeneralParticleSourceXMessenger.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"

namespace MACE::inline Extension::Geant4X {

GeneralParticleSourceXMessenger::GeneralParticleSourceXMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fPulseWidth{} {

    fDirectory = std::make_unique<G4UIdirectory>("/GPSX/");
    fDirectory->SetGuidance("General particle source extension.");

    fPulseWidth = std::make_unique<G4UIcmdWithADoubleAndUnit>("/GPSX/PulseWidth", this);
    fPulseWidth->SetGuidance("Set pulse width of beam.");
    fPulseWidth->SetParameterName("T", false);
    fPulseWidth->SetUnitCategory("Time");
    fPulseWidth->AvailableForStates(G4State_Idle);
}

GeneralParticleSourceXMessenger::~GeneralParticleSourceXMessenger() = default;

auto GeneralParticleSourceXMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fPulseWidth.get()) {
        Deliver<GeneralParticleSourceX>([&](auto&& r) {
            r.PulseWidth(fPulseWidth->GetNewDoubleValue(value));
        });
    }
}

} // namespace MACE::inline Extension::Geant4X
