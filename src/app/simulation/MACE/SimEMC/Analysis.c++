#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/Geant4X/ConvertGeometry.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/SimEMC/Action/TrackingAction.h++"
#include "MACE/SimEMC/Analysis.h++"
#include "MACE/Simulation/Hit/EMCHit.h++"
#include "MACE/Simulation/Hit/EMCPMTHit.h++"
#include "MACE/Simulation/Hit/MCPHit.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/format.h"

#include <stdexcept>

namespace MACE::SimEMC {

Analysis::Analysis() :
    PassiveSingleton{},
    fFilePath{"SimEMC_untitled"},
    fFileMode{"NEW"},
    fCoincidenceWithEMC{true},
    fCoincidenceWithMCP{false},
    fLastUsedFullFilePath{},
    fFile{},
    fDecayVertexOutput{},
    fEMCSimHitOutput{},
    fEMCPMTHitOutput{},
    fMCPSimHitOutput{},
    fDecayVertex{},
    fEMCHit{},
    fEMCPMTHit{},
    fMCPHit{},
    fMessengerRegister{this} {}

auto Analysis::RunBegin(G4int runID) -> void {
    // open ROOT file
    auto fullFilePath{MPIX::ParallelizePath(fFilePath).replace_extension(".root").generic_string()};
    const auto filePathChanged{fullFilePath != fLastUsedFullFilePath};
    fFile = TFile::Open(fullFilePath.c_str(), filePathChanged ? fFileMode.c_str() : "UPDATE",
                        "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fFile == nullptr) {
        throw std::runtime_error{fmt::format("MACE::SimEMC::Analysis::RunBegin: Cannot open file '{}' with mode '{}'",
                                             fullFilePath, fFileMode)};
    }
    fLastUsedFullFilePath = std::move(fullFilePath);
    // save geometry
    if (filePathChanged and Env::MPIEnv::Instance().OnCommWorldMaster()) {
        Geant4X::ConvertGeometryToTMacro("SimEMC_gdml", "SimEMC.gdml")->Write();
    }
    // cd into run directory
    const auto runDirectory{fmt::format("G4Run{}", runID)};
    fFile->mkdir(runDirectory.c_str());
    fFile->cd(runDirectory.c_str());
    if (TrackingAction::Instance().SaveDecayVertexData()) { fDecayVertexOutput.emplace("SimDecayVertex"); }
    fEMCSimHitOutput.emplace("EMCSimHit");
    fEMCPMTHitOutput.emplace("EMCPMTHit");
    fMCPSimHitOutput.emplace("MCPSimHit");
}

auto Analysis::EventEnd() -> void {
    const auto emcPassed{not fCoincidenceWithEMC or fEMCHit == nullptr or fEMCHit->size() > 0};
    const auto mcpPassed{not fCoincidenceWithMCP or fMCPHit == nullptr or fMCPHit->size() > 0};
    if (emcPassed and mcpPassed) {
        if (fDecayVertex and fDecayVertexOutput) { *fDecayVertexOutput << *fDecayVertex; }
        if (fEMCHit) { *fEMCSimHitOutput << *fEMCHit; }
        if (fEMCPMTHit) { *fEMCPMTHitOutput << *fEMCPMTHit; }
        if (fMCPHit) { *fMCPSimHitOutput << *fMCPHit; }
    }
    fDecayVertex = {};
    fEMCHit = {};
    fEMCPMTHit = {};
    fMCPHit = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    // write data
    if (fDecayVertexOutput) { fDecayVertexOutput->Write(); }
    fEMCSimHitOutput->Write();
    fEMCPMTHitOutput->Write();
    fMCPSimHitOutput->Write();
    // close file
    fFile->Close(option);
    delete fFile;
    // reset output
    fDecayVertexOutput.reset();
    fEMCSimHitOutput.reset();
    fEMCPMTHitOutput.reset();
    fMCPSimHitOutput.reset();
}

} // namespace MACE::SimEMC
