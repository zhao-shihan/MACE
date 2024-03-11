#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/SimEMC/Analysis.h++"
#include "MACE/Simulation/Hit/EMCHit.h++"
#include "MACE/Simulation/Hit/EMCPMTHit.h++"
#include "MACE/Simulation/Hit/MCPHit.h++"
#include "MACE/Utility/ConvertG4Geometry.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/format.h"

#include <stdexcept>

namespace MACE::SimEMC {

Analysis::Analysis() :
    PassiveSingleton{},
    fFilePath{"SimEMC_untitled"},
    fFileOption{"NEW"},
    fEnableCoincidenceOfEMC{true},
    fEnableCoincidenceOfMCP{false},
    fLastUsedFullFilePath{},
    fFile{},
    fEMCSimHitOutput{},
    fEMCPMTSimHitOutput{},
    fMCPSimHitOutput{},
    fEMCHit{},
    fEMCPMTHit{},
    fMCPHit{},
    fMessengerRegister{this} {}

auto Analysis::RunBegin(G4int runID) -> void {
    // open ROOT file
    auto fullFilePath{MPIX::ParallelizePath(fFilePath).replace_extension(".root").generic_string()};
    const auto filePathChanged{fullFilePath != fLastUsedFullFilePath};
    fFile = TFile::Open(fullFilePath.c_str(), filePathChanged ? fFileOption.c_str() : "UPDATE",
                        "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fFile == nullptr) {
        throw std::runtime_error{fmt::format("MACE::SimEMC::Analysis::RunBegin: Cannot open file '{}' with option '{}'",
                                             fullFilePath, fFileOption)};
    }
    fLastUsedFullFilePath = std::move(fullFilePath);
    // save geometry
    if (filePathChanged and Env::MPIEnv::Instance().OnCommWorldMaster()) {
        ConvertG4GeometryToTMacro("SimEMC_gdml", "SimEMC.gdml")->Write();
    }
    // cd into run directory
    const auto runDirectory{fmt::format("G4Run{}", runID)};
    fFile->mkdir(runDirectory.c_str());
    fFile->cd(runDirectory.c_str());
    fEMCSimHitOutput.emplace("EMCSimHit");
    fEMCPMTSimHitOutput.emplace("EMCPMTSimHit");
    fMCPSimHitOutput.emplace("MCPSimHit");
}

auto Analysis::EventEnd() -> void {
    const auto emcTriggered{not fEnableCoincidenceOfEMC or fEMCHit == nullptr or fEMCHit->size() > 0};
    const auto mcpTriggered{not fEnableCoincidenceOfMCP or fMCPHit == nullptr or fMCPHit->size() > 0};
    if (emcTriggered and mcpTriggered) {
        if (fEMCHit) { *fEMCSimHitOutput << *fEMCHit; }
        if (fEMCPMTHit) { *fEMCPMTSimHitOutput << *fEMCPMTHit; }
        if (fMCPHit) { *fMCPSimHitOutput << *fMCPHit; }
    }
    fEMCHit = {};
    fEMCPMTHit = {};
    fMCPHit = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    // write data
    fEMCSimHitOutput->Write();
    fEMCPMTSimHitOutput->Write();
    fMCPSimHitOutput->Write();
    // close file
    fFile->Close(option);
    delete fFile;
}

} // namespace MACE::SimEMC
