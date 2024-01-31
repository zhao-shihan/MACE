#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/SimMACE/Analysis.h++"
#include "MACE/Simulation/Hit/CDCHit.h++"
#include "MACE/Simulation/Hit/EMCHit.h++"
#include "MACE/Simulation/Hit/MCPHit.h++"

#include "TFile.h"

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
    fEMCSimHitOutput{},
    fMCPSimHitOutput{},
    fCDCHit{},
    fEMCHit{},
    fMCPHit{},
    fMessengerRegister{this} {}

auto Analysis::RunBegin(G4int runID) -> void {
    const auto fullFilePath{MPIX::ParallelizePath(fFilePath, ".root").generic_string()};
    fFile = TFile::Open(fullFilePath.c_str(), fFileOption.c_str(),
                        "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fFile == nullptr) {
        throw std::runtime_error{fmt::format("MACE::SimMACE::Analysis::RunBegin: Cannot open file \"{}\"", fullFilePath)};
    }
    fCDCSimHitOutput.emplace(fmt::format("G4Run{}_CDCSimHit", runID));
    fMCPSimHitOutput.emplace(fmt::format("G4Run{}_MCPSimHit", runID));
    fEMCSimHitOutput.emplace(fmt::format("G4Run{}_EMCSimHit", runID));
}

auto Analysis::EventEnd() -> void {
    const auto cdcTriggered{not fCoincidenceWithCDC or fCDCHit == nullptr or fCDCHit->size() > 0};
    const auto emcTriggered{not fCoincidenceWithEMC or fEMCHit == nullptr or fEMCHit->size() > 0};
    const auto mcpTriggered{not fCoincidenceWithMCP or fMCPHit == nullptr or fMCPHit->size() > 0};
    if (emcTriggered and mcpTriggered and cdcTriggered) {
        if (fCDCHit) { *fCDCSimHitOutput << *fCDCHit; }
        if (fEMCHit) { *fEMCSimHitOutput << *fEMCHit; }
        if (fMCPHit) { *fMCPSimHitOutput << *fMCPHit; }
    }
    fCDCHit = {};
    fEMCHit = {};
    fMCPHit = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    fCDCSimHitOutput->Write();
    fEMCSimHitOutput->Write();
    fMCPSimHitOutput->Write();
    fFile->Close(option);
    delete fFile;
}

} // namespace MACE::SimMACE
