#pragma once

#include "MACE/Data/Output.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimEMC/Messenger/AnalysisMessenger.h++"

#include "G4Types.hh"

#include "gsl/gsl"

#include <filesystem>
#include <memory>
#include <optional>
#include <utility>

class TFile;

namespace MACE::inline Simulation::inline Hit {
class EMCHit;
class EMCPMTHit;
class MCPHit;
} // namespace MACE::inline Simulation::inline Hit

namespace MACE::SimEMC {

class Analysis final : public Env::Memory::PassiveSingleton<Analysis> {
public:
    Analysis();

    auto FilePath(std::filesystem::path path) -> void { fFilePath = std::move(path); }
    auto FileOption(std::string option) -> void { fFileOption = std::move(option); }
    auto EnableCoincidenceOfEMC(G4bool val) -> void { fEnableCoincidenceOfEMC = val; }
    auto EnableCoincidenceOfMCP(G4bool val) -> void { fEnableCoincidenceOfMCP = val; }

    auto RunBegin(G4int runID) -> void;

    auto SubmitEMCHC(gsl::not_null<std::vector<gsl::owner<Simulation::EMCHit*>>*> hc) -> void { fEMCHit = hc; }
    auto SubmitEMCPMTHC(gsl::not_null<std::vector<gsl::owner<Simulation::EMCPMTHit*>>*> hc) -> void { fEMCPMTHit = hc; }
    auto SubmitMCPHC(gsl::not_null<std::vector<gsl::owner<Simulation::MCPHit*>>*> hc) -> void { fMCPHit = hc; }
    auto EventEnd() -> void;

    auto RunEnd(Option_t* option = nullptr) -> void;

private:
    std::filesystem::path fFilePath;
    std::string fFileOption;
    G4bool fEnableCoincidenceOfEMC;
    G4bool fEnableCoincidenceOfMCP;

    gsl::owner<TFile*> fFile;
    std::optional<Data::Output<Data::EMCSimHit>> fEMCSimHitOutput;
    std::optional<Data::Output<Data::EMCPMTSimHit>> fEMCPMTSimHitOutput;
    std::optional<Data::Output<Data::MCPSimHit>> fMCPSimHitOutput;

    const std::vector<gsl::owner<Simulation::EMCHit*>>* fEMCHit;
    const std::vector<gsl::owner<Simulation::EMCPMTHit*>>* fEMCPMTHit;
    const std::vector<gsl::owner<Simulation::MCPHit*>>* fMCPHit;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::SimEMC
