#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/SimEMC/Analysis.h++"
#include "MACE/Simulation/Hit/EMCHit.h++"
#include "MACE/Simulation/Hit/EMCPMTHit.h++"
#include "MACE/Simulation/Hit/MCPHit.h++"

#include "TFile.h"

#include "fmt/format.h"

#include <stdexcept>

namespace MACE::SimEMC {

Analysis::Analysis() :
    PassiveSingleton{},
    fFilePath{"SimEMC_untitled"},
    fFileOption{"NEW"},
    fEnableCoincidenceOfEMC{true},
    fEnableCoincidenceOfMCP{false},
    fFile{},
    fEMCSimHitOutput{},
    fEMCPMTSimHitOutput{},
    fMCPSimHitOutput{},
    fEMCHit{},
    fEMCPMTHit{},
    fMCPHit{},
    fMessengerRegister{this} {}

auto Analysis::RunBegin(G4int runID) -> void {
    const auto fullFilePath{MPIX::ParallelizePath(fFilePath, ".root").generic_string()};
    fFile = TFile::Open(fullFilePath.c_str(), fFileOption.c_str(),
                        "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fFile == nullptr) {
        throw std::runtime_error{fmt::format("MACE::SimEMC::Analysis::RunBegin: Cannot open file \"{}\"", fullFilePath)};
    }
    fEMCSimHitOutput.emplace(fmt::format("G4Run{}_EMCSimHit", runID));
    fEMCPMTSimHitOutput.emplace(fmt::format("G4Run{}_EMCPMTSimHit", runID));
    fMCPSimHitOutput.emplace(fmt::format("G4Run{}_MCPSimHit", runID));
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
    fEMCSimHitOutput->Write();
    fEMCPMTSimHitOutput->Write();
    fMCPSimHitOutput->Write();
    fFile->Close(option);
    delete fFile;
}

} // namespace MACE::SimEMC
