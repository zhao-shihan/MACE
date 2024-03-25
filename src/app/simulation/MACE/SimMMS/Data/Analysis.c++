#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/Geant4X/ConvertGeometry.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/SimMMS/Data/Analysis.h++"
#include "MACE/Simulation/Hit/CDCHit.h++"
#include "MACE/Simulation/Hit/EMCHit.h++"
#include "MACE/Simulation/Hit/MCPHit.h++"
#include "MACE/Simulation/Hit/STCHit.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/format.h"

#include <stdexcept>

namespace MACE::SimMMS::Data {

Analysis::Analysis() :
    PassiveSingleton{},
    fFilePath{"SimMMS_untitled"},
    fFileMode{"NEW"},
    fCoincidenceWithCDC{true},
    fCoincidenceWithSTC{true},
    fSaveCDCHitData{true},
    fLastUsedFullFilePath{},
    fFile{},
    fDecayVertexOutput{},
    fCDCSimHitOutput{},
    fCDCSimTrackOutput{},
    fSTCSimHitOutput{},
    fDecayVertex{},
    fCDCHit{},
    fCDCTrack{},
    fSTCHit{},
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
    fDecayVertexOutput.emplace("DecayVertex");
    fCDCSimHitOutput.emplace("CDCSimHit");
    fCDCSimTrackOutput.emplace("CDCSimTrack");
    fSTCSimHitOutput.emplace("STCSimHit");
}

auto Analysis::EventEnd() -> void {
    const auto cdcPassed{not fCoincidenceWithCDC or fCDCTrack == nullptr or fCDCTrack->size() > 0};
    const auto stcPassed{not fCoincidenceWithSTC or fSTCHit == nullptr or fSTCHit->size() > 0};
    if (cdcPassed and stcPassed) {
        if (fDecayVertex) { *fDecayVertexOutput << *fDecayVertex; }
        if (fCDCHit and fSaveCDCHitData) { *fCDCSimHitOutput << *fCDCHit; }
        if (fCDCTrack) { *fCDCSimTrackOutput << *fCDCTrack; }
        if (fSTCHit) { *fSTCSimHitOutput << *fSTCHit; }
    }
    fDecayVertex = {};
    fCDCHit = {};
    fCDCTrack = {};
    fSTCHit = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    // write data
    fDecayVertexOutput->Write();
    fCDCSimHitOutput->Write();
    fCDCSimTrackOutput->Write();
    fSTCSimHitOutput->Write();
    // close file
    fFile->Close(option);
    delete fFile;
}

} // namespace MACE::SimMMS::Data
