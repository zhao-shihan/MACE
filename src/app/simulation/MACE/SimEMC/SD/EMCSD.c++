#include "MACE/Detector/Description/EMC.h++"
#include "MACE/SimEMC/Analysis.h++"
#include "MACE/SimEMC/SD/EMCSD.h++"

#include "G4HCofThisEvent.hh"
#include "G4OpticalPhoton.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

#include <utility>

namespace MACE::SimEMC::inline SD {

EMCSD::EMCSD(const G4String& sdName) :
    NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fEventID{-1},
    fHit{},
    fHitsCollection{} {
    collectionName.insert(sdName + "HC");
}

auto EMCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    // int cellTotalNumber = Detector::Description::EMC::Instance().CellTotalNumber();

    fHitsCollection = new EMCHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);

    // for (auto i = 0; i < cellTotalNumber; i++) {
    //     fHitsCollection->insert(new EMCHit());
    // }
}

auto EMCSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step = *theStep;
    const auto& track = *step.GetTrack();
    const auto& particle = *track.GetDefinition();

    if (&particle != G4OpticalPhoton::Definition()) {
        const auto cellID = track.GetVolume()->GetCopyNo();
        // find or new a hit
        const auto [iter, isNewHit] = fHit.try_emplace(cellID, std::make_unique_for_overwrite<EMCHit>());
        auto& hit = *iter->second;
        if (isNewHit) {
            const auto& preStepPoint = *step.GetPreStepPoint();
            const auto& touchable = *preStepPoint.GetTouchable();
            // transform hit position to local coordinate
            const auto hitPosition = *touchable.GetRotation() * (preStepPoint.GetPosition() - touchable.GetTranslation());
            // calculate (Ek0, p0)
            const auto vertexEk = track.GetVertexKineticEnergy();
            const auto vertexMomentum = track.GetVertexMomentumDirection() * std::sqrt(vertexEk * (vertexEk + 2 * particle.GetPDGMass()));

            Get<"CellID">(hit) = cellID;
            Get<"t">(hit) = preStepPoint.GetGlobalTime();
            Get<"E">(hit) = 0;
            Get<"EvtID">(hit) = fEventID;
            Get<"TrkID">(hit) = track.GetTrackID();
            Get<"PDGID">(hit) = particle.GetPDGEncoding();
            Get<"Ek">(hit) = preStepPoint.GetKineticEnergy();
            Get<"x">(hit) = hitPosition;
            Get<"p">(hit) = preStepPoint.GetMomentum();
            Get<"t0">(hit) = track.GetGlobalTime() - track.GetLocalTime();
            Get<"x0">(hit) = track.GetVertexPosition();
            Get<"Ek0">(hit) = vertexEk;
            Get<"p0">(hit) = vertexMomentum;
        }
        Get<"E">(hit) += step.GetTotalEnergyDeposit();
        return true;
    }
    return false;
}

auto EMCSD::EndOfEvent(G4HCofThisEvent*) -> void {
    for (auto&& [_, hit] : fHit) {
        if (Get<"E">(*hit) == 0) { continue; }
        fHitsCollection->insert(hit.release());
    }
    fHit.clear();
    Analysis::Instance().SubmitEMCHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimEMC::inline SD
