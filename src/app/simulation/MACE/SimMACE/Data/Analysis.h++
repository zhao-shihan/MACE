#pragma once

#include "MACE/Data/CDCTrack.h++"
#include "MACE/Data/Output.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimMACE/Data/Model/DecayVertex.h++"
#include "MACE/SimMACE/Data/AnalysisMessenger.h++"

#include "G4Types.hh"

#include "gsl/gsl"

#include <filesystem>
#include <memory>
#include <utility>

class TFile;

namespace MACE::inline Simulation::inline Hit {
class CDCHit;
class EMCHit;
class MCPHit;
} // namespace MACE::inline Simulation::inline Hit

namespace MACE::SimMACE::Data {

class Analysis final : public Env::Memory::PassiveSingleton<Analysis> {
public:
    Analysis();

    auto FilePath(std::filesystem::path path) -> void { fFilePath = std::move(path); }
    auto FileOption(std::string option) -> void { fFileOption = std::move(option); }
    auto CoincidenceWithCDC(bool val) -> void { fCoincidenceWithMCP = val; }
    auto CoincidenceWithMCP(bool val) -> void { fCoincidenceWithMCP = val; }
    auto CoincidenceWithEMC(bool val) -> void { fCoincidenceWithEMC = val; }

    auto RunBegin(G4int runID) -> void;

    auto SubmitDecayVertexData(const std::vector<std::unique_ptr<MACE::Data::Tuple<Data::DecayVertex>>>& data) -> void { fDecayVertex = &data; }
    auto SubmitCDCHC(gsl::not_null<const std::vector<gsl::owner<Simulation::CDCHit*>>*> hc) -> void { fCDCHit = hc; }
    auto SubmitCDCTrackData(const std::vector<std::unique_ptr<MACE::Data::Tuple<MACE::Data::CDCSimTrack>>>& data) -> void { fCDCTrack = &data; }
    auto SubmitEMCHC(gsl::not_null<const std::vector<gsl::owner<Simulation::EMCHit*>>*> hc) -> void { fEMCHit = hc; }
    auto SubmitMCPHC(gsl::not_null<const std::vector<gsl::owner<Simulation::MCPHit*>>*> hc) -> void { fMCPHit = hc; }
    auto EventEnd() -> void;

    auto RunEnd(Option_t* option = nullptr) -> void;

private:
    std::filesystem::path fFilePath;
    std::string fFileOption;
    bool fCoincidenceWithCDC;
    bool fCoincidenceWithMCP;
    bool fCoincidenceWithEMC;

    gsl::owner<TFile*> fFile;
    std::optional<MACE::Data::Output<Data::DecayVertex>> fDecayVertexOutput;
    std::optional<MACE::Data::Output<MACE::Data::CDCSimHit>> fCDCSimHitOutput;
    std::optional<MACE::Data::Output<MACE::Data::CDCSimTrack>> fCDCSimTrackOutput;
    std::optional<MACE::Data::Output<MACE::Data::EMCSimHit>> fEMCSimHitOutput;
    std::optional<MACE::Data::Output<MACE::Data::MCPSimHit>> fMCPSimHitOutput;

    const std::vector<std::unique_ptr<MACE::Data::Tuple<Data::DecayVertex>>>* fDecayVertex;
    const std::vector<gsl::owner<Simulation::CDCHit*>>* fCDCHit;
    const std::vector<std::unique_ptr<MACE::Data::Tuple<MACE::Data::CDCSimTrack>>>* fCDCTrack;
    const std::vector<gsl::owner<Simulation::EMCHit*>>* fEMCHit;
    const std::vector<gsl::owner<Simulation::MCPHit*>>* fMCPHit;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::SimMACE::Data
