#pragma once

#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Data/SimVertex.h++"
#include "MACE/SimMACE/Messenger/AnalysisMessenger.h++"
#include "MACE/Simulation/Analysis/MMSTruthTracker.h++"

#include "Mustard/Data/Output.h++"
#include "Mustard/Data/Tuple.h++"
#include "Mustard/Simulation/AnalysisBase.h++"

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

class Analysis final : public Mustard::Simulation::AnalysisBase<Analysis, "SimMACE"> {
public:
    Analysis();

    auto CoincidenceWithMMS(bool val) -> void { fCoincidenceWithMMS = val; }
    auto CoincidenceWithMCP(bool val) -> void { fCoincidenceWithMCP = val; }
    auto CoincidenceWithEMC(bool val) -> void { fCoincidenceWithEMC = val; }
    auto SaveCDCHitData(bool val) -> void { fSaveCDCHitData = val; }
    auto SaveTTCHitData(bool val) -> void { fSaveTTCHitData = val; }

    auto SubmitPrimaryVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>& data) -> void { fPrimaryVertex = &data; }
    auto SubmitDecayVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>& data) -> void { fDecayVertex = &data; }
    auto SubmitTTCHC(const std::vector<gsl::owner<TTCHit*>>& hc) -> void { fTTCHit = &hc; }
    auto SubmitCDCHC(const std::vector<gsl::owner<CDCHit*>>& hc) -> void { fCDCHit = &hc; }
    auto SubmitMCPHC(const std::vector<gsl::owner<MCPHit*>>& hc) -> void { fMCPHit = &hc; }
    auto SubmitEMCHC(const std::vector<gsl::owner<EMCHit*>>& hc) -> void { fEMCHit = &hc; }

private:
    auto RunBeginUserAction(int runID) -> void override;
    auto EventEndUserAction() -> void override;
    auto RunEndUserAction(int) -> void override;

private:
    bool fCoincidenceWithMMS;
    bool fCoincidenceWithMCP;
    bool fCoincidenceWithEMC;
    bool fSaveCDCHitData;
    bool fSaveTTCHitData;

    std::optional<Mustard::Data::Output<Data::SimPrimaryVertex>> fPrimaryVertexOutput;
    std::optional<Mustard::Data::Output<Data::SimDecayVertex>> fDecayVertexOutput;
    std::optional<Mustard::Data::Output<Data::TTCSimHit>> fTTCSimHitOutput;
    std::optional<Mustard::Data::Output<Data::CDCSimHit>> fCDCSimHitOutput;
    std::optional<Mustard::Data::Output<Data::MMSSimTrack>> fMMSSimTrackOutput;
    std::optional<Mustard::Data::Output<Data::MCPSimHit>> fMCPSimHitOutput;
    std::optional<Mustard::Data::Output<Data::EMCSimHit>> fEMCSimHitOutput;

    const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>* fPrimaryVertex;
    const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>* fDecayVertex;
    const std::vector<gsl::owner<TTCHit*>>* fTTCHit;
    const std::vector<gsl::owner<CDCHit*>>* fCDCHit;
    const std::vector<gsl::owner<MCPHit*>>* fMCPHit;
    const std::vector<gsl::owner<EMCHit*>>* fEMCHit;

    Simulation::Analysis::MMSTruthTracker fMMSTruthTracker;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::SimMACE
