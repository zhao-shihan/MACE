#include "MACE/SimEMC/Action/RunAction.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"
// #include "MACE/SimEMC/Analysis.h++"

#include "G4AnalysisManager.hh"

namespace MACE::SimEMC::inline Action {

auto RunAction::BeginOfRunAction(const G4Run* /* run */) -> void {
    // Analysis::Instance().RunBegin(run);
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile(MPIX::ParallelizePath("EMCdemo.root").generic_string());

    analysisManager->CreateNtuple("cellHit", "result");
    analysisManager->CreateNtupleIColumn("eventID");
    analysisManager->CreateNtupleIColumn("cellID");
    analysisManager->CreateNtupleDColumn("energyDeposit");
    analysisManager->CreateNtupleIColumn("nPhotons");
    analysisManager->FinishNtuple();

    analysisManager->CreateNtuple("pulse", "result");
    analysisManager->CreateNtupleIColumn("eventID");
    analysisManager->CreateNtupleIColumn("pmtID");
    analysisManager->CreateNtupleDColumn("nToF");
    analysisManager->FinishNtuple();
}

auto RunAction::EndOfRunAction(const G4Run*) -> void {
    // Analysis::Instance().RunEnd();
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
    analysisManager->Clear();
}

} // namespace MACE::SimEMC::inline Action
