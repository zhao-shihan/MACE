#pragma once

#include "MACE/Data/CDCTrack.h++"
#include "MACE/Data/Output.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimMACE/Data/AnalysisMessenger.h++"
#include "MACE/SimMACE/Data/Model/DecayVertex.h++"

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
class TTCHit;
} // namespace MACE::inline Simulation::inline Hit

namespace MACE::SimMACE::Data {

class Analysis final : public Env::Memory::PassiveSingleton<Analysis> {
public:
    Analysis();

    auto FilePath(std::filesystem::path path) -> void { fFilePath = std::move(path); }
    auto FileMode(std::string mode) -> void { fFileMode = std::move(mode); }
    auto CoincidenceWithCDC(bool val) -> void { fCoincidenceWithCDC = val; }
    auto CoincidenceWithTTC(bool val) -> void { fCoincidenceWithTTC = val; }
    auto CoincidenceWithMCP(bool val) -> void { fCoincidenceWithMCP = val; }
    auto CoincidenceWithEMC(bool val) -> void { fCoincidenceWithEMC = val; }
    auto SaveCDCHitData(bool val) -> void { fSaveCDCHitData = val; }

    auto RunBegin(G4int runID) -> void;

    auto SubmitDecayVertexData(const std::vector<std::unique_ptr<MACE::Data::Tuple<Data::DecayVertex>>>& data) -> void { fDecayVertex = &data; }
    auto SubmitCDCHC(gsl::not_null<const std::vector<gsl::owner<Simulation::CDCHit*>>*> hc) -> void { fCDCHit = hc; }
    auto SubmitCDCTrackData(const std::vector<std::unique_ptr<MACE::Data::Tuple<MACE::Data::CDCSimTrack>>>& data) -> void { fCDCTrack = &data; }
    auto SubmitTTCHC(gsl::not_null<const std::vector<gsl::owner<Simulation::TTCHit*>>*> hc) -> void { fTTCHit = hc; }
    auto SubmitMCPHC(gsl::not_null<const std::vector<gsl::owner<Simulation::MCPHit*>>*> hc) -> void { fMCPHit = hc; }
    auto SubmitEMCHC(gsl::not_null<const std::vector<gsl::owner<Simulation::EMCHit*>>*> hc) -> void { fEMCHit = hc; }
    auto EventEnd() -> void;

    auto RunEnd(Option_t* option = {}) -> void;

private:
    std::filesystem::path fFilePath;
    std::string fFileMode;
    bool fCoincidenceWithCDC;
    bool fCoincidenceWithTTC;
    bool fCoincidenceWithMCP;
    bool fCoincidenceWithEMC;
    bool fSaveCDCHitData;

    std::filesystem::path fLastUsedFullFilePath;

    gsl::owner<TFile*> fFile;
    std::optional<MACE::Data::Output<Data::DecayVertex>> fDecayVertexOutput;
    std::optional<MACE::Data::Output<MACE::Data::CDCSimHit>> fCDCSimHitOutput;
    std::optional<MACE::Data::Output<MACE::Data::CDCSimTrack>> fCDCSimTrackOutput;
    std::optional<MACE::Data::Output<MACE::Data::TTCSimHit>> fTTCSimHitOutput;
    std::optional<MACE::Data::Output<MACE::Data::MCPSimHit>> fMCPSimHitOutput;
    std::optional<MACE::Data::Output<MACE::Data::EMCSimHit>> fEMCSimHitOutput;

    const std::vector<std::unique_ptr<MACE::Data::Tuple<Data::DecayVertex>>>* fDecayVertex;
    const std::vector<gsl::owner<Simulation::CDCHit*>>* fCDCHit;
    const std::vector<std::unique_ptr<MACE::Data::Tuple<MACE::Data::CDCSimTrack>>>* fCDCTrack;
    const std::vector<gsl::owner<Simulation::TTCHit*>>* fTTCHit;
    const std::vector<gsl::owner<Simulation::MCPHit*>>* fMCPHit;
    const std::vector<gsl::owner<Simulation::EMCHit*>>* fEMCHit;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::SimMACE::Data
