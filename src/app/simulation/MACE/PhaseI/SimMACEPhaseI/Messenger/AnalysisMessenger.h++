#pragma once

#include "Mustard/Geant4X/Interface/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithABool;
class G4UIcmdWithAString;
class G4UIdirectory;

namespace MACE::PhaseI::SimMACEPhaseI {

class Analysis;
inline namespace Action {
class PrimaryGeneratorAction;
class TrackingAction;
} // namespace Action

inline namespace Messenger {

class AnalysisMessenger final : public Mustard::Geant4X::SingletonMessenger<AnalysisMessenger,
                                                                            Analysis,
                                                                            TrackingAction,
                                                                            PrimaryGeneratorAction> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    AnalysisMessenger();
    ~AnalysisMessenger() override;

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithAString> fFilePath;
    std::unique_ptr<G4UIcmdWithAString> fFileMode;
    std::unique_ptr<G4UIcmdWithABool> fSavePrimaryVertexData;
    std::unique_ptr<G4UIcmdWithABool> fSaveDecayVertexData;
    std::unique_ptr<G4UIcmdWithABool> fCoincidenceWithMRPC;
    std::unique_ptr<G4UIcmdWithABool> fCoincidenceWithECAL;
};

} // namespace Messenger

} // namespace MACE::PhaseI::SimMACEPhaseI
