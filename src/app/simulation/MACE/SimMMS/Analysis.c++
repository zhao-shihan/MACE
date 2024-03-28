#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/Geant4X/ConvertGeometry.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/SimMMS/Action/TrackingAction.h++"
#include "MACE/SimMMS/Analysis.h++"
#include "MACE/Simulation/Hit/CDCHit.h++"
#include "MACE/Simulation/Hit/EMCHit.h++"
#include "MACE/Simulation/Hit/MCPHit.h++"
#include "MACE/Simulation/Hit/TTCHit.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/format.h"

#include <stdexcept>

namespace MACE::SimMMS {

Analysis::Analysis() :
    PassiveSingleton{},
    fFilePath{"SimMMS_untitled"},
    fFileMode{"NEW"},
    fCoincidenceWithCDC{true},
    fCoincidenceWithTTC{true},
    fSaveCDCHitData{true},
    fSaveTTCHitData{true},
    fLastUsedFullFilePath{},
    fFile{},
    fDecayVertexOutput{},
    fCDCSimHitOutput{},
    fTTCSimHitOutput{},
    fMMSSimTrackOutput{},
    fDecayVertex{},
    fCDCHit{},
    fTTCHit{},
    fMMSTruthTracker{},
    fMessengerRegister{this} {}

auto Analysis::RunBegin(G4int runID) -> void {
    // open ROOT file
    auto fullFilePath{MPIX::ParallelizePath(fFilePath).replace_extension(".root").generic_string()};
    const auto filePathChanged{fullFilePath != fLastUsedFullFilePath};
    fFile = TFile::Open(fullFilePath.c_str(), filePathChanged ? fFileMode.c_str() : "UPDATE",
                        "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fFile == nullptr) {
        throw std::runtime_error{fmt::format("MACE::SimMMS::Analysis::RunBegin: Cannot open file '{}' with mode '{}'",
                                             fullFilePath, fFileMode)};
    }
    fLastUsedFullFilePath = std::move(fullFilePath);
    // save geometry
    if (filePathChanged and Env::MPIEnv::Instance().OnCommWorldMaster()) {
        Geant4X::ConvertGeometryToTMacro("SimMMS_gdml", "SimMMS.gdml")->Write();
    }
    // cd into run directory
    const auto runDirectory{fmt::format("G4Run{}", runID)};
    fFile->mkdir(runDirectory.c_str());
    fFile->cd(runDirectory.c_str());
    if (TrackingAction::Instance().SaveDecayVertexData()) { fDecayVertexOutput.emplace("SimDecayVertex"); }
    if (fSaveCDCHitData) { fCDCSimHitOutput.emplace("CDCSimHit"); }
    if (fSaveTTCHitData) { fTTCSimHitOutput.emplace("TTCSimHit"); }
    fMMSSimTrackOutput.emplace("MMSSimTrack");
}

auto Analysis::EventEnd() -> void {
    const auto mmsTrack{fCDCHit and fTTCHit ?
                            std::optional{fMMSTruthTracker(*fCDCHit, *fTTCHit)} :
                            std::nullopt};
    const auto cdcPassed{not fCoincidenceWithCDC or fCDCHit == nullptr or fCDCHit->size() > 0};
    const auto ttcPassed{not fCoincidenceWithTTC or fTTCHit == nullptr or fTTCHit->size() > 0};
    const auto mmsPassed{mmsTrack == std::nullopt or mmsTrack->size() > 0};
    if (cdcPassed and ttcPassed and mmsPassed) {
        if (fDecayVertex and fDecayVertexOutput) { *fDecayVertexOutput << *fDecayVertex; }
        if (fCDCHit and fCDCSimHitOutput) { *fCDCSimHitOutput << *fCDCHit; }
        if (fTTCHit and fTTCSimHitOutput) { *fTTCSimHitOutput << *fTTCHit; }
        if (mmsTrack) { *fMMSSimTrackOutput << *mmsTrack; }
    }
    fDecayVertex = {};
    fCDCHit = {};
    fTTCHit = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    // write data
    if (fDecayVertexOutput) { fDecayVertexOutput->Write(); }
    if (fCDCSimHitOutput) { fCDCSimHitOutput->Write(); }
    if (fTTCSimHitOutput) { fTTCSimHitOutput->Write(); }
    fMMSSimTrackOutput->Write();
    // close file
    fFile->Close(option);
    delete fFile;
    // reset output
    fDecayVertexOutput.reset();
    fCDCSimHitOutput.reset();
    fTTCSimHitOutput.reset();
    fMMSSimTrackOutput.reset();
}

} // namespace MACE::SimMMS
