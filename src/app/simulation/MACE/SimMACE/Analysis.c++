#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/Geant4X/ConvertGeometry.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/SimMACE/Action/TrackingAction.h++"
#include "MACE/SimMACE/Analysis.h++"
#include "MACE/Simulation/Hit/CDCHit.h++"
#include "MACE/Simulation/Hit/EMCHit.h++"
#include "MACE/Simulation/Hit/MCPHit.h++"
#include "MACE/Simulation/Hit/TTCHit.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/format.h"

#include <optional>
#include <stdexcept>

namespace MACE::SimMACE {

Analysis::Analysis() :
    PassiveSingleton{},
    fFilePath{"SimMACE_untitled"},
    fFileMode{"NEW"},
    fCoincidenceWithCDC{true},
    fCoincidenceWithTTC{true},
    fCoincidenceWithMMS{true},
    fCoincidenceWithMCP{true},
    fCoincidenceWithEMC{true},
    fSaveCDCHitData{true},
    fSaveTTCHitData{true},
    fLastUsedFullFilePath{},
    fFile{},
    fDecayVertexOutput{},
    fCDCSimHitOutput{},
    fTTCSimHitOutput{},
    fMMSSimTrackOutput{},
    fMCPSimHitOutput{},
    fEMCSimHitOutput{},
    fDecayVertex{},
    fCDCHit{},
    fTTCHit{},
    fMCPHit{},
    fEMCHit{},
    fMMSTruthTracker{},
    fMessengerRegister{this} {}

auto Analysis::RunBegin(G4int runID) -> void {
    // open ROOT file
    auto fullFilePath{MPIX::ParallelizePath(fFilePath).replace_extension(".root").generic_string()};
    const auto filePathChanged{fullFilePath != fLastUsedFullFilePath};
    fFile = TFile::Open(fullFilePath.c_str(), filePathChanged ? fFileMode.c_str() : "UPDATE",
                        "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fFile == nullptr) {
        throw std::runtime_error{fmt::format("MACE::SimMACE::Analysis::RunBegin: Cannot open file '{}' with mode '{}'",
                                             fullFilePath, fFileMode)};
    }
    fLastUsedFullFilePath = std::move(fullFilePath);
    // save geometry
    if (filePathChanged and Env::MPIEnv::Instance().OnCommWorldMaster()) {
        Geant4X::ConvertGeometryToTMacro("SimMACE_gdml", "SimMACE.gdml")->Write();
    }
    // cd into run directory
    const auto runDirectory{fmt::format("G4Run{}", runID)};
    fFile->mkdir(runDirectory.c_str());
    fFile->cd(runDirectory.c_str());
    if (TrackingAction::Instance().SaveDecayVertexData()) { fDecayVertexOutput.emplace("SimDecayVertex"); }
    if (fSaveCDCHitData) { fCDCSimHitOutput.emplace("CDCSimHit"); }
    if (fSaveTTCHitData) { fTTCSimHitOutput.emplace("TTCSimHit"); }
    fMMSSimTrackOutput.emplace("MMSSimTrack");
    fMCPSimHitOutput.emplace("MCPSimHit");
    fEMCSimHitOutput.emplace("EMCSimHit");
}

auto Analysis::EventEnd() -> void {
    const auto mmsTrack{fCDCHit and fTTCHit ?
                            std::optional{fMMSTruthTracker(*fCDCHit, *fTTCHit)} :
                            std::nullopt};
    const auto cdcPassed{not fCoincidenceWithCDC or fCDCHit == nullptr or fCDCHit->size() > 0};
    const auto ttcPassed{not fCoincidenceWithTTC or fTTCHit == nullptr or fTTCHit->size() > 0};
    const auto mmsPassed{not fCoincidenceWithMMS or mmsTrack == std::nullopt or mmsTrack->size() > 0};
    const auto mcpPassed{not fCoincidenceWithMCP or fMCPHit == nullptr or fMCPHit->size() > 0};
    const auto emcPassed{not fCoincidenceWithEMC or fEMCHit == nullptr or fEMCHit->size() > 0};
    if (cdcPassed and ttcPassed and mmsPassed and mcpPassed and emcPassed) {
        if (fDecayVertex and fDecayVertexOutput) { *fDecayVertexOutput << *fDecayVertex; }
        if (fCDCHit and fCDCSimHitOutput) { *fCDCSimHitOutput << *fCDCHit; }
        if (fTTCHit and fTTCSimHitOutput) { *fTTCSimHitOutput << *fTTCHit; }
        if (mmsTrack) { *fMMSSimTrackOutput << *mmsTrack; }
        if (fMCPHit) { *fMCPSimHitOutput << *fMCPHit; }
        if (fEMCHit) { *fEMCSimHitOutput << *fEMCHit; }
    }
    fDecayVertex = {};
    fCDCHit = {};
    fTTCHit = {};
    fMCPHit = {};
    fEMCHit = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    // write data
    if (fDecayVertexOutput) { fDecayVertexOutput->Write(); }
    if (fCDCSimHitOutput) { fCDCSimHitOutput->Write(); }
    if (fTTCSimHitOutput) { fTTCSimHitOutput->Write(); }
    fMMSSimTrackOutput->Write();
    fMCPSimHitOutput->Write();
    fEMCSimHitOutput->Write();
    // close file
    fFile->Close(option);
    delete fFile;
    // reset output
    fDecayVertexOutput.reset();
    fCDCSimHitOutput.reset();
    fTTCSimHitOutput.reset();
    fMMSSimTrackOutput.reset();
    fMCPSimHitOutput.reset();
    fEMCSimHitOutput.reset();
}

} // namespace MACE::SimMACE
