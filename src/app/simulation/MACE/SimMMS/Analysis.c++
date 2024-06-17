#include "MACE/SimMMS/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimMMS/Action/TrackingAction.h++"
#include "MACE/SimMMS/Analysis.h++"
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
    fPrimaryVertexOutput{},
    fDecayVertexOutput{},
    fCDCSimHitOutput{},
    fTTCSimHitOutput{},
    fMMSSimTrackOutput{},
    fPrimaryVertex{},
    fDecayVertex{},
    fCDCHit{},
    fTTCHit{},
    fMMSTruthTracker{},
    fMessengerRegister{this} {}

auto Analysis::RunBegin(G4int runID) -> void {
    // open ROOT file
    auto fullFilePath{Mustard::MPIX::ParallelizePath(fFilePath).replace_extension(".root").generic_string()};
    const auto filePathChanged{fullFilePath != fLastUsedFullFilePath};
    fFile = TFile::Open(fullFilePath.c_str(), filePathChanged ? fFileMode.c_str() : "UPDATE",
                        "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fFile == nullptr) {
        throw std::runtime_error{fmt::format("MACE::SimMMS::Analysis::RunBegin: Cannot open file '{}' with mode '{}'",
                                             fullFilePath, fFileMode)};
    }
    fLastUsedFullFilePath = std::move(fullFilePath);
    // save geometry
    if (filePathChanged and Mustard::Env::MPIEnv::Instance().OnCommWorldMaster()) {
        Mustard::Geant4X::ConvertGeometryToTMacro("SimMMS_gdml", "SimMMS.gdml")->Write();
    }
    // initialize outputs
    if (PrimaryGeneratorAction::Instance().SavePrimaryVertexData()) { fPrimaryVertexOutput.emplace(fmt::format("G4Run{}/SimPrimaryVertex", runID)); }
    if (TrackingAction::Instance().SaveDecayVertexData()) { fDecayVertexOutput.emplace(fmt::format("G4Run{}/SimDecayVertex", runID)); }
    if (fSaveCDCHitData) { fCDCSimHitOutput.emplace(fmt::format("G4Run{}/CDCSimHit", runID)); }
    if (fSaveTTCHitData) { fTTCSimHitOutput.emplace(fmt::format("G4Run{}/TTCSimHit", runID)); }
    fMMSSimTrackOutput.emplace(fmt::format("G4Run{}/MMSSimTrack", runID));
}

auto Analysis::EventEnd() -> void {
    const auto mmsTrack{fCDCHit and fTTCHit ?
                            std::optional{fMMSTruthTracker(*fCDCHit, *fTTCHit)} :
                            std::nullopt};
    const auto cdcPassed{not fCoincidenceWithCDC or fCDCHit == nullptr or fCDCHit->size() > 0};
    const auto ttcPassed{not fCoincidenceWithTTC or fTTCHit == nullptr or fTTCHit->size() > 0};
    const auto mmsPassed{mmsTrack == std::nullopt or mmsTrack->size() > 0};
    if (cdcPassed and ttcPassed and mmsPassed) {
        if (fPrimaryVertex and fPrimaryVertexOutput) { fPrimaryVertexOutput->Fill(*fPrimaryVertex); }
        if (fDecayVertex and fDecayVertexOutput) { fDecayVertexOutput->Fill(*fDecayVertex); }
        if (fCDCHit and fCDCSimHitOutput) { fCDCSimHitOutput->Fill(*fCDCHit); }
        if (fTTCHit and fTTCSimHitOutput) { fTTCSimHitOutput->Fill(*fTTCHit); }
        if (mmsTrack) { fMMSSimTrackOutput->Fill(*mmsTrack); }
    }
    fPrimaryVertex = {};
    fDecayVertex = {};
    fCDCHit = {};
    fTTCHit = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    // write data
    if (fPrimaryVertexOutput) { fPrimaryVertexOutput->Write(); }
    if (fDecayVertexOutput) { fDecayVertexOutput->Write(); }
    if (fCDCSimHitOutput) { fCDCSimHitOutput->Write(); }
    if (fTTCSimHitOutput) { fTTCSimHitOutput->Write(); }
    fMMSSimTrackOutput->Write();
    // close file
    fFile->Close(option);
    delete fFile;
    // reset output
    fPrimaryVertexOutput.reset();
    fDecayVertexOutput.reset();
    fCDCSimHitOutput.reset();
    fTTCSimHitOutput.reset();
    fMMSSimTrackOutput.reset();
}

} // namespace MACE::SimMMS
