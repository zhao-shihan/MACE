#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/SimMACE/Analysis.h++"
#include "MACE/Simulation/Hit/CDCHit.h++"
#include "MACE/Simulation/Hit/EMCHit.h++"
#include "MACE/Simulation/Hit/MCPHit.h++"
#include "MACE/Utility/ConvertG4Geometry.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/format.h"

#include <stdexcept>

namespace MACE::SimMACE {

Analysis::Analysis() :
    PassiveSingleton{},
    fFilePath{"SimMACE_untitled"},
    fFileOption{"NEW"},
    fCoincidenceWithCDC{true},
    fCoincidenceWithMCP{true},
    fCoincidenceWithEMC{true},
    fFile{},
    fCDCSimHitOutput{},
    fCDCSimTrackOutput{},
    fEMCSimHitOutput{},
    fMCPSimHitOutput{},
    fCDCHit{},
    fCDCTrack{},
    fEMCHit{},
    fMCPHit{},
    fMessengerRegister{this} {}

auto Analysis::RunBegin() -> void {
    const auto fullFilePath{MPIX::ParallelizePath(fFilePath, ".root").generic_string()};
    fFile = TFile::Open(fullFilePath.c_str(), fFileOption.c_str(),
                        "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fFile == nullptr) {
        throw std::runtime_error{fmt::format("MACE::SimMACE::Analysis::RunBegin: Cannot open file \"{}\"", fullFilePath)};
    }
    fCDCSimHitOutput.emplace("CDCSimHit");
    fCDCSimTrackOutput.emplace("CDCSimTrack");
    fMCPSimHitOutput.emplace("MCPSimHit");
    fEMCSimHitOutput.emplace("EMCSimHit");
}

auto Analysis::EventEnd() -> void {
    const auto cdcTriggered{not fCoincidenceWithCDC or fCDCHit == nullptr or fCDCHit->size() > 0};
    const auto emcTriggered{not fCoincidenceWithEMC or fEMCHit == nullptr or fEMCHit->size() > 0};
    const auto mcpTriggered{not fCoincidenceWithMCP or fMCPHit == nullptr or fMCPHit->size() > 0};
    if (emcTriggered and mcpTriggered and cdcTriggered) {
        if (fCDCHit) { *fCDCSimHitOutput << *fCDCHit; }
        if (fCDCTrack) { *fCDCSimTrackOutput << *fCDCTrack; }
        if (fEMCHit) { *fEMCSimHitOutput << *fEMCHit; }
        if (fMCPHit) { *fMCPSimHitOutput << *fMCPHit; }
    }
    fCDCHit = {};
    fCDCTrack = {};
    fEMCHit = {};
    fMCPHit = {};
}

auto Analysis::RunEnd(G4int runID, Option_t* option) -> void {
    const auto runDirectory{fmt::format("G4Run{}", runID)};
    fFile->mkdir(runDirectory.c_str());
    fFile->cd(runDirectory.c_str());

    // write geometry
    if (Env::MPIEnv::Instance().OnCommWorldMaster()) {
        ConvertG4GeometryToTMacro("SimMACE_gdml", "SimMACE.gdml")->Write();
    }
    // write data
    fCDCSimHitOutput->Write();
    fCDCSimTrackOutput->Write();
    fEMCSimHitOutput->Write();
    fMCPSimHitOutput->Write();

    fFile->cd();
    fFile->Close(option);
    delete fFile;
}

} // namespace MACE::SimMACE
