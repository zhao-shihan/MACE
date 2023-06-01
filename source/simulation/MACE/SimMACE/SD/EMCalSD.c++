#include "MACE/SimMACE/Analysis.h++"
#include "MACE/SimMACE/SD/EMCalSD.h++"

#include "G4Gamma.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

namespace MACE::SimMACE::inline SD {

EMCalSD::EMCalSD(const G4String& sdName) :
    NonMoveableBase(),
    G4VSensitiveDetector(sdName),
    fEventID(-1),
    fHitsCollection(nullptr) {
    collectionName.insert(sdName + "HC");
}

void EMCalSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new EMCalHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool EMCalSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) {
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
        const auto hit = new EMCalHit;
        hit->Time().Value(preStepPoint.GetGlobalTime());
        hit->EnergyDeposition().Value(preStepPoint.GetKineticEnergy());
        hit->MCEventID().Value(fEventID);
        hit->MCTrackID().Value(track.GetTrackID());
        hit->PDGCode().Value(particle.GetPDGEncoding());
        hit->Position().Value(hitPosition);
        hit->Momentum().Value(preStepPoint.GetMomentum());
        hit->VertexTime().Value(track.GetGlobalTime() - track.GetLocalTime());
        hit->VertexPosition().Value(track.GetVertexPosition());
        hit->VertexKineticEnergy().Value(vertexEk);
        hit->VertexMomentum().Value(vertexMomentum);
        fHitsCollection->insert(hit);
        return true;
    }
    return false;
}

void EMCalSD::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance().SubmitEMCalHC(fHitsCollection->GetVector());
}

} // namespace MACE::SimMACE::inline SD
