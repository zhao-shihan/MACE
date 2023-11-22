#include "MACE/SimMACE/Analysis.h++"
#include "MACE/SimMACE/SD/EMCSD.h++"

#include "G4Gamma.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

namespace MACE::SimMACE::inline SD {

EMCSD::EMCSD(const G4String& sdName) :
    NonMoveableBase(),
    G4VSensitiveDetector(sdName),
    fEventID(-1),
    fHitsCollection(nullptr) {
    collectionName.insert(sdName + "HC");
}

void EMCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new EMCHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool EMCSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) {
    const auto& step = *theStep;
    const auto& track = *step.GetTrack();
    const auto& particle = *track.GetDefinition();
    if (step.IsFirstStepInVolume() and track.GetCurrentStepNumber() > 1 and     // is coming from outside, and
        (particle.GetPDGCharge() != 0 or &particle == G4Gamma::Definition())) { // is a charged particle or gamma
        const auto& preStepPoint = *step.GetPreStepPoint();
        const auto& touchable = *preStepPoint.GetTouchable();
        // transform hit position to local coordinate
        const auto hitPosition = *touchable.GetRotation() * (preStepPoint.GetPosition() - touchable.GetTranslation());
        // calculate (Ek0, p0)
        const auto vertexEk = track.GetVertexKineticEnergy();
        const auto vertexMomentum = track.GetVertexMomentumDirection() * std::sqrt(vertexEk * (vertexEk + 2 * particle.GetPDGMass()));
        // new a hit
        const auto hit = new EMCHit;
        hit->Get<"CellID">() = 0;
        hit->Get<"t">() = preStepPoint.GetGlobalTime();
        hit->Get<"E">() = preStepPoint.GetKineticEnergy();
        hit->Get<"EvtID">() = fEventID;
        hit->Get<"TrkID">() = track.GetTrackID();
        hit->Get<"PDGID">() = particle.GetPDGEncoding();
        hit->Get<"Ek">() = preStepPoint.GetKineticEnergy();
        hit->Get<"x">() = hitPosition;
        hit->Get<"p">() = preStepPoint.GetMomentum();
        hit->Get<"t0">() = track.GetGlobalTime() - track.GetLocalTime();
        hit->Get<"x0">() = track.GetVertexPosition();
        hit->Get<"Ek0">() = vertexEk;
        hit->Get<"p0">() = vertexMomentum;
        fHitsCollection->insert(hit);
        return true;
    }
    return false;
}

void EMCSD::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance().SubmitEMCHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimMACE::inline SD
