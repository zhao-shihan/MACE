#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithAString;
class G4UIdirectory;

namespace MACE::SimMMS::inline Messenger {

class DetectorMessenger final : public Geant4X::SingletonMessenger<DetectorMessenger> {
    friend Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger();
    ~DetectorMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithAString> fImportDescription;
    std::unique_ptr<G4UIcmdWithAString> fExportDescription;
    std::unique_ptr<G4UIcmdWithAString> fIxportDescription;
};

} // namespace MACE::SimMMS::inline Messenger
