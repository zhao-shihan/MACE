#pragma once

#include "MACE/Data/MMSTrack.h++"
#include "Mustard/Data/Output.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Data/SimVertex.h++"
#include "Mustard/Data/Tuple.h++"
#include "Mustard/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimMACE/Messenger/AnalysisMessenger.h++"
#include "MACE/Simulation/Analysis/MMSTruthTracker.h++"

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

namespace MACE::SimMACE {

class Analysis final : public Mustard::Env::Memory::PassiveSingleton<Analysis> {
public:
    Analysis();

    auto FilePath(std::filesystem::path path) -> void { fFilePath = std::move(path); }
    auto FileMode(std::string mode) -> void { fFileMode = std::move(mode); }
    auto CoincidenceWithCDC(bool val) -> void { fCoincidenceWithCDC = val; }
    auto CoincidenceWithTTC(bool val) -> void { fCoincidenceWithTTC = val; }
    auto CoincidenceWithMMS(bool val) -> void { fCoincidenceWithMMS = val; }
    auto CoincidenceWithMCP(bool val) -> void { fCoincidenceWithMCP = val; }
    auto CoincidenceWithEMC(bool val) -> void { fCoincidenceWithEMC = val; }
    auto SaveCDCHitData(bool val) -> void { fSaveCDCHitData = val; }
    auto SaveTTCHitData(bool val) -> void { fSaveTTCHitData = val; }

    auto RunBegin(G4int runID) -> void;

    auto SubmitPrimaryVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>& data) -> void { fPrimaryVertex = &data; }
    auto SubmitDecayVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>& data) -> void { fDecayVertex = &data; }
    auto SubmitCDCHC(const std::vector<gsl::owner<CDCHit*>>& hc) -> void { fCDCHit = &hc; }
    auto SubmitTTCHC(const std::vector<gsl::owner<TTCHit*>>& hc) -> void { fTTCHit = &hc; }
    auto SubmitMCPHC(const std::vector<gsl::owner<MCPHit*>>& hc) -> void { fMCPHit = &hc; }
    auto SubmitEMCHC(const std::vector<gsl::owner<EMCHit*>>& hc) -> void { fEMCHit = &hc; }
    auto EventEnd() -> void;

    auto RunEnd(Option_t* option = {}) -> void;

private:
    std::filesystem::path fFilePath;
    std::string fFileMode;
    bool fCoincidenceWithCDC;
    bool fCoincidenceWithTTC;
    bool fCoincidenceWithMMS;
    bool fCoincidenceWithMCP;
    bool fCoincidenceWithEMC;
    bool fSaveCDCHitData;
    bool fSaveTTCHitData;

    std::filesystem::path fLastUsedFullFilePath;

    gsl::owner<TFile*> fFile;
    std::optional<Mustard::Data::Output<Data::SimPrimaryVertex>> fPrimaryVertexOutput;
    std::optional<Mustard::Data::Output<Data::SimDecayVertex>> fDecayVertexOutput;
    std::optional<Mustard::Data::Output<Data::CDCSimHit>> fCDCSimHitOutput;
    std::optional<Mustard::Data::Output<Data::TTCSimHit>> fTTCSimHitOutput;
    std::optional<Mustard::Data::Output<Data::MMSSimTrack>> fMMSSimTrackOutput;
    std::optional<Mustard::Data::Output<Data::MCPSimHit>> fMCPSimHitOutput;
    std::optional<Mustard::Data::Output<Data::EMCSimHit>> fEMCSimHitOutput;

    const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>* fPrimaryVertex;
    const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>* fDecayVertex;
    const std::vector<gsl::owner<CDCHit*>>* fCDCHit;
    const std::vector<gsl::owner<TTCHit*>>* fTTCHit;
    const std::vector<gsl::owner<MCPHit*>>* fMCPHit;
    const std::vector<gsl::owner<EMCHit*>>* fEMCHit;

    Simulation::Analysis::MMSTruthTracker fMMSTruthTracker;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::SimMACE
