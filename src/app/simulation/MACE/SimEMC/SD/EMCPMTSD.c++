#include "MACE/SimEMC/Analysis.h++"
#include "MACE/SimEMC/SD/EMCPMTSD.h++"

#include "G4HCofThisEvent.hh"
#include "G4OpticalPhoton.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

#include <utility>

namespace MACE::SimEMC::inline SD {

EMCPMTSD::EMCPMTSD(const G4String& sdName) :
    NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fEventID{-1},
    fHit{},
    fHitsCollection{} {
    collectionName.insert(sdName + "HC");
}

auto EMCPMTSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHitsCollection = new EMCPMTHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto EMCPMTSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    // auto particleDefinition = theStep->GetTrack()->GetDefinition();
    // if (particleDefinition != G4OpticalPhoton::OpticalPhotonDefinition()) { return false; }
    // theStep->GetTrack()->SetTrackStatus(fStopAndKill);
    // auto hit = new EMCPMTHit;
    // auto globalTime = theStep->GetPostStepPoint()->GetGlobalTime();
    // auto copyNo = theStep->GetTrack()->GetVolume()->GetCopyNo();
    // hit->Time(globalTime);
    // hit->CellID(copyNo);
    // fHitsCollection->insert(hit);
    // return true;
    const auto& step{*theStep};
    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};

    if (&particle == G4OpticalPhoton::Definition()) {
        step.GetTrack()->SetTrackStatus(fStopAndKill);
        const auto unitID{track.GetVolume()->GetCopyNo()};
        // find or new a hit
        const auto [iter, isNewHit]{fHit.try_emplace(unitID, std::make_unique_for_overwrite<EMCPMTHit>())};
        auto& hit{*iter->second};
        if (isNewHit) {
            const auto& preStepPoint{*step.GetPreStepPoint()};
            const auto& touchable{*preStepPoint.GetTouchable()};
            // transform hit position to local coordinate
            const auto hitPosition{*touchable.GetRotation() * (preStepPoint.GetPosition() - touchable.GetTranslation())};
            // calculate (Ek0, p0)
            const auto vertexEk{track.GetVertexKineticEnergy()};
            const auto vertexMomentum{track.GetVertexMomentumDirection() * std::sqrt(vertexEk * (vertexEk + 2 * particle.GetPDGMass()))};

            Get<"EvtID">(hit) = fEventID;
            Get<"HitID">(hit) = -1;
            Get<"UnitID">(hit) = unitID;
            Get<"t">(hit) = preStepPoint.GetGlobalTime();
            Get<"EMCHitID">(hit) = -1;
        }
        return true;
    }
    return false;
}

auto EMCPMTSD::EndOfEvent(G4HCofThisEvent*) -> void {
    for (auto&& [_, hit] : fHit) {
        fHitsCollection->insert(hit.release());
    }
    fHit.clear();
    Analysis::Instance().SubmitEMCPMTHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimEMC::inline SD
