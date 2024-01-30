#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithABool;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIdirectory;

namespace MACE::SimEMC {

class Analysis;

inline namespace Messenger {

class AnalysisMessenger final : public Env::Memory::Singleton<AnalysisMessenger>,
                                public G4UImessenger {
    friend Env::Memory::SingletonInstantiator;

private:
    AnalysisMessenger();
    ~AnalysisMessenger();

public:
    auto AssignTo(gsl::not_null<Analysis*> ana) -> void { fAnalysis = ana; }

    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    Analysis* fAnalysis;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithABool> fEnableCoincidenceOfEMC;
    std::unique_ptr<G4UIcmdWithABool> fEnableCoincidenceOfMCP;
    std::unique_ptr<G4UIcmdWithAString> fFilePath;
    std::unique_ptr<G4UIcmdWithAString> fFileOption;
};

} // namespace Messenger

} // namespace MACE::SimEMC
