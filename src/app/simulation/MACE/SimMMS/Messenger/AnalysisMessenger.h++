#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithABool;
class G4UIcmdWithAString;
class G4UIdirectory;

namespace MACE::SimMMS {

class Analysis;

inline namespace Messenger {

class AnalysisMessenger final : public Geant4X::SingletonMessenger<AnalysisMessenger,
                                                                   Analysis> {
    friend Env::Memory::SingletonInstantiator;

private:
    AnalysisMessenger();
    ~AnalysisMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithAString> fFilePath;
    std::unique_ptr<G4UIcmdWithAString> fFileMode;
    std::unique_ptr<G4UIcmdWithABool> fCoincidenceWithCDC;
    std::unique_ptr<G4UIcmdWithABool> fCoincidenceWithSTC;
    std::unique_ptr<G4UIcmdWithABool> fSaveCDCHitData;
};

} // namespace Messenger

} // namespace MACE::SimMMS
