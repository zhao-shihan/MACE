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
    fFileOption{"UPDATE"},
    fEnableCoincidenceOfEMC{true},
    fEnableCoincidenceOfMCP{true},
    fFile{},
    fEMCSimHitOutput{},
    fEMCPMTSimHitOutput{},
    fMCPSimHitOutput{},
    fEMCHitList{},
    fEMCPMTHitList{},
    fMCPHitList{},
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
    const auto emcTriggered{not fEnableCoincidenceOfEMC or fEMCHitList == nullptr or fEMCHitList->size() > 0};
    const auto mcpTriggered{not fEnableCoincidenceOfMCP or fMCPHitList == nullptr or fMCPHitList->size() > 0};
    if (emcTriggered and mcpTriggered) {
        if (fEMCHitList) { *fEMCSimHitOutput << *fEMCHitList; }
        if (fEMCPMTHitList) { *fEMCPMTSimHitOutput << *fEMCPMTHitList; }
        if (fMCPHitList) { *fMCPSimHitOutput << *fMCPHitList; }
    }
    fEMCHitList = {};
    fEMCPMTHitList = {};
    fMCPHitList = {};
}

auto Analysis::RunEnd(Option_t* option) -> void {
    fEMCSimHitOutput->Write();
    fEMCPMTSimHitOutput->Write();
    fMCPSimHitOutput->Write();
    fFile->Close(option);
    delete fFile;
}

} // namespace MACE::SimEMC
