#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/Geant4X/Utility/ConvertGeometry.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"
#include "MACE/SimEMC/Action/PrimaryGeneratorAction.h++"
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
    fPrimaryVertexOutput{},
    fDecayVertexOutput{},
    fEMCSimHitOutput{},
    fEMCPMTHitOutput{},
    fMCPSimHitOutput{},
    fPrimaryVertex{},
    fDecayVertex{},
    fEMCHit{},
    fEMCPMTHit{},
    fMCPHit{},
    fMessengerRegister{this} {}

auto Analysis::RunBegin(G4int runID) -> void {
    // open ROOT file
    auto fullFilePath{Mustard::MPIX::ParallelizePath(fFilePath).replace_extension(".root").generic_string()};
    const auto filePathChanged{fullFilePath != fLastUsedFullFilePath};
    fFile = TFile::Open(fullFilePath.c_str(), filePathChanged ? fFileMode.c_str() : "UPDATE",
                        "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fFile == nullptr) {
        throw std::runtime_error{fmt::format("MACE::SimEMC::Analysis::RunBegin: Cannot open file '{}' with mode '{}'",
                                             fullFilePath, fFileMode)};
    }
    fLastUsedFullFilePath = std::move(fullFilePath);
    // save geometry
    if (filePathChanged and Mustard::Env::MPIEnv::Instance().OnCommWorldMaster()) {
        Mustard::Geant4X::ConvertGeometryToTMacro("SimEMC_gdml", "SimEMC.gdml")->Write();
    }
    // initialize outputs
    if (PrimaryGeneratorAction::Instance().SavePrimaryVertexData()) { fPrimaryVertexOutput.emplace(fmt::format("G4Run{}/SimPrimaryVertex", runID)); }
    if (TrackingAction::Instance().SaveDecayVertexData()) { fDecayVertexOutput.emplace(fmt::format("G4Run{}/SimDecayVertex", runID)); }
    fEMCSimHitOutput.emplace(fmt::format("G4Run{}/EMCSimHit", runID));
    fEMCPMTHitOutput.emplace(fmt::format("G4Run{}/EMCPMTHit", runID));
    fMCPSimHitOutput.emplace(fmt::format("G4Run{}/MCPSimHit", runID));
}

auto Analysis::EventEnd() -> void {
    const auto emcPassed{not fCoincidenceWithEMC or fEMCHit == nullptr or fEMCHit->size() > 0};
    const auto mcpPassed{not fCoincidenceWithMCP or fMCPHit == nullptr or fMCPHit->size() > 0};
    if (emcPassed and mcpPassed) {
        if (fPrimaryVertex and fPrimaryVertexOutput) { fPrimaryVertexOutput->Fill(*fPrimaryVertex); }
        if (fDecayVertex and fDecayVertexOutput) { fDecayVertexOutput->Fill(*fDecayVertex); }
        if (fEMCHit) { fEMCSimHitOutput->Fill(*fEMCHit); }
        if (fEMCPMTHit) { fEMCPMTHitOutput->Fill(*fEMCPMTHit); }
        if (fMCPHit) { fMCPSimHitOutput->Fill(*fMCPHit); }
    }
    fPrimaryVertex = {};
    fDecayVertex = {};
    fEMCHit = {};
    fEMCPMTHit = {};
    fMCPHit = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    // write data
    if (fPrimaryVertexOutput) { fPrimaryVertexOutput->Write(); }
    if (fDecayVertexOutput) { fDecayVertexOutput->Write(); }
    fEMCSimHitOutput->Write();
    fEMCPMTHitOutput->Write();
    fMCPSimHitOutput->Write();
    // close file
    fFile->Close(option);
    delete fFile;
    // reset output
    fPrimaryVertexOutput.reset();
    fDecayVertexOutput.reset();
    fEMCSimHitOutput.reset();
    fEMCPMTHitOutput.reset();
    fMCPSimHitOutput.reset();
}

} // namespace MACE::SimEMC
