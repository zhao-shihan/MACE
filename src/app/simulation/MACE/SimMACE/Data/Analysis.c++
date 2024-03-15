#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/Geant4X/ConvertGeometry.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/SimMACE/Data/Analysis.h++"
#include "MACE/Simulation/Hit/CDCHit.h++"
#include "MACE/Simulation/Hit/EMCHit.h++"
#include "MACE/Simulation/Hit/MCPHit.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/format.h"

#include <stdexcept>

namespace MACE::SimMACE::Data {

Analysis::Analysis() :
    PassiveSingleton{},
    fFilePath{"SimMACE_untitled"},
    fFileMode{"NEW"},
    fCoincidenceWithCDC{true},
    fCoincidenceWithMCP{true},
    fCoincidenceWithEMC{true},
    fLastUsedFullFilePath{},
    fFile{},
    fDecayVertexOutput{},
    fCDCSimHitOutput{},
    fCDCSimTrackOutput{},
    fEMCSimHitOutput{},
    fMCPSimHitOutput{},
    fCDCHit{},
    fCDCTrack{},
    fEMCHit{},
    fMCPHit{},
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
    fDecayVertexOutput.emplace("DecayVertex");
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
        if (fDecayVertex) { *fDecayVertexOutput << *fDecayVertex; }
        if (fCDCHit) { *fCDCSimHitOutput << *fCDCHit; }
        if (fCDCTrack) { *fCDCSimTrackOutput << *fCDCTrack; }
        if (fEMCHit) { *fEMCSimHitOutput << *fEMCHit; }
        if (fMCPHit) { *fMCPSimHitOutput << *fMCPHit; }
    }
    fDecayVertex = {};
    fCDCHit = {};
    fCDCTrack = {};
    fEMCHit = {};
    fMCPHit = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    // write data
    fDecayVertexOutput->Write();
    fCDCSimHitOutput->Write();
    fCDCSimTrackOutput->Write();
    fEMCSimHitOutput->Write();
    fMCPSimHitOutput->Write();
    // close file
    fFile->Close(option);
    delete fFile;
}

} // namespace MACE::SimMACE::Data
