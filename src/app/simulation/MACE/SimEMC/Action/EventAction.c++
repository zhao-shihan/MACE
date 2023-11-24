#include "MACE/Detector/Description/EMC.h++"
#include "MACE/SimEMC/Action/EventAction.h++"
#include "MACE/SimEMC/Hit/EMCHit.h++"
#include "MACE/SimEMC/Hit/PMTHit.h++"
#include "MACE/SimEMC/SD/EMCSD.h++"
#include "MACE/SimEMC/SD/PMTSD.h++"
// #include "MACE/SimEMC/Analysis.h++"

#include "G4AnalysisManager.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Trajectory.hh"
#include "G4TrajectoryContainer.hh"

namespace MACE::SimEMC::inline Action {

auto EventAction::BeginOfEventAction(const G4Event*) -> void {}

auto EventAction::EndOfEventAction(const G4Event* event) -> void {
    auto emcHCid = G4SDManager::GetSDMpointer()->GetCollectionID("EMCCrystalHC");
    auto emcHC = static_cast<EMCHitCollection*>(event->GetHCofThisEvent()->GetHC(emcHCid));
    auto pmtHCid = G4SDManager::GetSDMpointer()->GetCollectionID("EMCCathodeHC");
    auto pmtHC = static_cast<PMTHitCollection*>(event->GetHCofThisEvent()->GetHC(pmtHCid));

    int cellTotalNumber = Detector::Description::EMC::Instance().CellTotalNumber();

    auto eventID = event->GetEventID();
    auto analysisManager = G4AnalysisManager::Instance();

    for (auto i = 0; i < cellTotalNumber; i++) {

        auto energyDeposit = (*emcHC)[i]->Energy();

        if (energyDeposit > 0.) {
            analysisManager->FillNtupleIColumn(0, 0, eventID);
            analysisManager->FillNtupleIColumn(0, 1, i);
            analysisManager->FillNtupleDColumn(0, 2, energyDeposit);
            analysisManager->FillNtupleIColumn(0, 3, pmtHC->entries());
            analysisManager->AddNtupleRow(0);
        }
    }

    for (long unsigned int j = 0; j < pmtHC->entries(); j++) {

        auto pmtHit = (*pmtHC)[j];

        analysisManager->FillNtupleIColumn(1, 0, eventID);
        analysisManager->FillNtupleIColumn(1, 1, pmtHit->CopyNo());
        analysisManager->FillNtupleDColumn(1, 2, pmtHit->Time());
        analysisManager->AddNtupleRow(1);
    }
}

} // namespace MACE::SimEMC::inline Action
