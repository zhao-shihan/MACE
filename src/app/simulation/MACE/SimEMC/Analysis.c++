#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/SimEMC/Analysis.h++"
#include "MACE/SimEMC/Hit/EMCHit.h++"
#include "MACE/SimEMC/Hit/MCPHit.h++"
#include "MACE/SimEMC/Hit/PMTHit.h++"
#include "MACE/SimEMC/Messenger/AnalysisMessenger.h++"

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
    fPMTSimHitOutput{},
    fMCPSimHitOutput{},
    fEMCHitList{},
    fPMTHitList{},
    fMCPHitList{} {
    AnalysisMessenger::Instance().AssignTo(this);
}

auto Analysis::RunBegin(G4int runID) -> void {
    const auto fullFilePath{MPIX::ParallelizePath(fFilePath, ".root").generic_string()};
    fFile = TFile::Open(fullFilePath.c_str(), fFileOption.c_str(),
                        "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fFile == nullptr) {
        throw std::runtime_error{fmt::format("MACE::SimEMC::Analysis::RunBegin: Cannot open file \"{}\"", fullFilePath)};
    }
    fEMCSimHitOutput = std::make_unique<Data::Output<Data::EMCSimHit>>(fmt::format("G4Run{}_EMCSimHit", runID));
    fPMTSimHitOutput = std::make_unique<Data::Output<Data::PMTSimHit>>(fmt::format("G4Run{}_PMTSimHit", runID));
    fMCPSimHitOutput = std::make_unique<Data::Output<Data::MCPSimHit>>(fmt::format("G4Run{}_MCPSimHit", runID));
}

auto Analysis::EventEnd() -> void {
    const auto emcTriggered = not fEnableCoincidenceOfEMC or fEMCHitList->size() > 0;
    const auto mcpTriggered = not fEnableCoincidenceOfMCP or fMCPHitList->size() > 0;
    if (emcTriggered and mcpTriggered) {
        *fEMCSimHitOutput << *fEMCHitList;
        *fPMTSimHitOutput << *fPMTHitList;
        *fMCPSimHitOutput << *fMCPHitList;
    }
}

auto Analysis::RunEnd(Option_t* option) -> void {
    fEMCSimHitOutput->Write();
    fPMTSimHitOutput->Write();
    fMCPSimHitOutput->Write();
    fFile->Close(option);
    delete fFile;
}

} // namespace MACE::SimEMC
