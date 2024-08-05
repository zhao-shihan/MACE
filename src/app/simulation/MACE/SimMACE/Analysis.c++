#include "MACE/SimMACE/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimMACE/Action/TrackingAction.h++"
#include "MACE/SimMACE/Analysis.h++"
#include "MACE/Simulation/Hit/CDCHit.h++"
#include "MACE/Simulation/Hit/EMCHit.h++"
#include "MACE/Simulation/Hit/MCPHit.h++"
#include "MACE/Simulation/Hit/TTCHit.h++"

#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/Geant4X/Utility/ConvertGeometry.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/format.h"

#include <optional>
#include <stdexcept>

namespace MACE::SimMACE {

Analysis::Analysis() :
    AnalysisBase{},
    fCoincidenceWithMMS{true},
    fCoincidenceWithMCP{true},
    fCoincidenceWithEMC{true},
    fSaveCDCHitData{true},
    fSaveTTCHitData{true},
    fPrimaryVertexOutput{},
    fDecayVertexOutput{},
    fTTCSimHitOutput{},
    fCDCSimHitOutput{},
    fMMSSimTrackOutput{},
    fMCPSimHitOutput{},
    fEMCSimHitOutput{},
    fPrimaryVertex{},
    fDecayVertex{},
    fCDCHit{},
    fTTCHit{},
    fMCPHit{},
    fEMCHit{},
    fMMSTruthTracker{},
    fMessengerRegister{this} {}

auto Analysis::RunBeginUserAction(int runID) -> void {
    if (PrimaryGeneratorAction::Instance().SavePrimaryVertexData()) { fPrimaryVertexOutput.emplace(fmt::format("G4Run{}/SimPrimaryVertex", runID)); }
    if (TrackingAction::Instance().SaveDecayVertexData()) { fDecayVertexOutput.emplace(fmt::format("G4Run{}/SimDecayVertex", runID)); }
    if (fSaveTTCHitData) { fTTCSimHitOutput.emplace(fmt::format("G4Run{}/TTCSimHit", runID)); }
    if (fSaveCDCHitData) { fCDCSimHitOutput.emplace(fmt::format("G4Run{}/CDCSimHit", runID)); }
    fMMSSimTrackOutput.emplace(fmt::format("G4Run{}/MMSSimTrack", runID));
    fMCPSimHitOutput.emplace(fmt::format("G4Run{}/MCPSimHit", runID));
    fEMCSimHitOutput.emplace(fmt::format("G4Run{}/EMCSimHit", runID));
}

auto Analysis::EventEndUserAction() -> void {
    const auto mmsTrack{fCDCHit and fTTCHit ?
                           std::optional{fMMSTruthTracker(*fCDCHit, *fTTCHit)} :
                           std::nullopt};
    const auto mmsPassed{not fCoincidenceWithMMS or mmsTrack == std::nullopt or mmsTrack->size() > 0};
    const auto mcpPassed{not fCoincidenceWithMCP or fMCPHit == nullptr or fMCPHit->size() > 0};
    const auto emcPassed{not fCoincidenceWithEMC or fEMCHit == nullptr or fEMCHit->size() > 0};
    if (mmsPassed and mcpPassed and emcPassed) {
        if (fPrimaryVertex and fPrimaryVertexOutput) { fPrimaryVertexOutput->Fill(*fPrimaryVertex); }
        if (fDecayVertex and fDecayVertexOutput) { fDecayVertexOutput->Fill(*fDecayVertex); }
        if (mmsTrack) {
            if (fTTCSimHitOutput) { fTTCSimHitOutput->Fill(*fTTCHit); }
            if (fCDCSimHitOutput) { fCDCSimHitOutput->Fill(*fCDCHit); }
            fMMSSimTrackOutput->Fill(*mmsTrack);
        }
        if (fMCPHit) { fMCPSimHitOutput->Fill(*fMCPHit); }
        if (fEMCHit) { fEMCSimHitOutput->Fill(*fEMCHit); }
    }
    fPrimaryVertex = {};
    fDecayVertex = {};
    fCDCHit = {};
    fTTCHit = {};
    fMCPHit = {};
    fEMCHit = {};
}

auto Analysis::RunEndUserAction(int runID) -> void {
    // write data
    if (fPrimaryVertexOutput) { fPrimaryVertexOutput->Write(); }
    if (fDecayVertexOutput) { fDecayVertexOutput->Write(); }
    if (fTTCSimHitOutput) { fTTCSimHitOutput->Write(); }
    if (fCDCSimHitOutput) { fCDCSimHitOutput->Write(); }
    fMMSSimTrackOutput->Write();
    fMCPSimHitOutput->Write();
    fEMCSimHitOutput->Write();
    // reset output
    fPrimaryVertexOutput.reset();
    fDecayVertexOutput.reset();
    fTTCSimHitOutput.reset();
    fCDCSimHitOutput.reset();
    fMMSSimTrackOutput.reset();
    fMCPSimHitOutput.reset();
    fEMCSimHitOutput.reset();
}

} // namespace MACE::SimMACE
