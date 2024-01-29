// #include "MACE/SimEMC/Analysis.h++"
#include "MACE/Detector/Description/EMC.h++"
#include "MACE/SimEMC/Hit/EMCHit.h++"
#include "MACE/SimEMC/SD/EMCSD.h++"

#include "G4HCofThisEvent.hh"
#include "G4OpticalPhoton.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

#include "fmt/format.h"

#include <utility>

namespace MACE::SimEMC::inline SD {

EMCSD::EMCSD(G4String name) :
    NonMoveableBase{},
    G4VSensitiveDetector{std::move(name)},
    fHitsCollection{} {
    collectionName.insert(SensitiveDetectorName + "HC");
}

auto EMCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    int cellTotalNumber = Detector::Description::EMC::Instance().NUnit();
    fHitsCollection = new EMCHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);

    for (auto i = 0; i < cellTotalNumber; i++) {
        fHitsCollection->insert(new EMCHit());
    }
}

auto EMCSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    auto fDefinition = theStep->GetTrack()->GetDefinition();
    if (fDefinition != G4OpticalPhoton::OpticalPhotonDefinition()) {
        auto fCopyNo = theStep->GetTrack()->GetVolume()->GetCopyNo();
        (*fHitsCollection)[fCopyNo]->Energy(theStep->GetTotalEnergyDeposit());
    }

    return true;
}

auto EMCSD::EndOfEvent(G4HCofThisEvent*) -> void {}

} // namespace MACE::SimEMC::inline SD
