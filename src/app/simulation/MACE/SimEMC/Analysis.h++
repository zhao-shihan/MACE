#pragma once

#include "MACE/Data/Output.h++"
#include "MACE/Data/SimDecayVertex.h++"
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
    auto FileMode(std::string mode) -> void { fFileMode = std::move(mode); }
    auto CoincidenceWithEMC(G4bool val) -> void { fCoincidenceWithEMC = val; }
    auto CoincidenceWithMCP(G4bool val) -> void { fCoincidenceWithMCP = val; }

    auto RunBegin(G4int runID) -> void;

    auto SubmitDecayVertexData(const std::vector<std::unique_ptr<Data::Tuple<Data::SimDecayVertex>>>& data) -> void { fDecayVertex = &data; }
    auto SubmitEMCHC(gsl::not_null<std::vector<gsl::owner<Simulation::EMCHit*>>*> hc) -> void { fEMCHit = hc; }
    auto SubmitEMCPMTHC(gsl::not_null<std::vector<gsl::owner<Simulation::EMCPMTHit*>>*> hc) -> void { fEMCPMTHit = hc; }
    auto SubmitMCPHC(gsl::not_null<std::vector<gsl::owner<Simulation::MCPHit*>>*> hc) -> void { fMCPHit = hc; }
    auto EventEnd() -> void;

    auto RunEnd(Option_t* option = {}) -> void;

private:
    std::filesystem::path fFilePath;
    std::string fFileMode;
    G4bool fCoincidenceWithEMC;
    G4bool fCoincidenceWithMCP;

    std::filesystem::path fLastUsedFullFilePath;

    gsl::owner<TFile*> fFile;
    std::optional<Data::Output<Data::SimDecayVertex>> fDecayVertexOutput;
    std::optional<Data::Output<Data::EMCSimHit>> fEMCSimHitOutput;
    std::optional<Data::Output<Data::EMCPMTHit>> fEMCPMTHitOutput;
    std::optional<Data::Output<Data::MCPSimHit>> fMCPSimHitOutput;

    const std::vector<std::unique_ptr<Data::Tuple<Data::SimDecayVertex>>>* fDecayVertex;
    const std::vector<gsl::owner<Simulation::EMCHit*>>* fEMCHit;
    const std::vector<gsl::owner<Simulation::EMCPMTHit*>>* fEMCPMTHit;
    const std::vector<gsl::owner<Simulation::MCPHit*>>* fMCPHit;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::SimEMC
