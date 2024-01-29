#include "MACE/SimMACE/Analysis.h++"
#include "MACE/SimMACE/SD/MCPSD.h++"

#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"
#include "G4RotationMatrix.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VProcess.hh"
#include "G4VTouchable.hh"

#include <cmath>
#include <string_view>

namespace MACE::SimMACE::inline SD {

MCPSD::MCPSD(const G4String& sdName) :
    NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fEventID{-1},
    fHitID{},
    fHitsCollection{} {
    collectionName.insert(sdName + "HC");
}

auto MCPSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHitID = 0;

    fHitsCollection = new MCPHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto MCPSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step{*theStep};
    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};
    if (step.IsFirstStepInVolume() and track.GetCurrentStepNumber() > 1 and // is coming from outside, and
        particle.GetPDGCharge() != 0) {                                     // is a charged particle.
        const auto& preStepPoint{*step.GetPreStepPoint()};
        const auto& touchable{*preStepPoint.GetTouchable()};
        // transform hit position to local coordinate
        const G4TwoVector hitPosition{*touchable.GetRotation() * (preStepPoint.GetPosition() - touchable.GetTranslation())};
        // calculate (E0, p0)
        const auto vertexEk{track.GetVertexKineticEnergy()};
        const auto vertexMomentum{track.GetVertexMomentumDirection() * std::sqrt(vertexEk * (vertexEk + 2 * particle.GetPDGMass()))};
        // track creator process
        const auto creatorProcess{track.GetCreatorProcess()};
        // assert event ID
        assert(fEventID >= 0);
        // new a hit
        const auto hit{new MCPHit};
        Get<"EvtID">(*hit) = fEventID;
        Get<"HitID">(*hit) = fHitID++;
        Get<"t">(*hit) = preStepPoint.GetGlobalTime();
        Get<"x">(*hit) = hitPosition;
        Get<"Ek">(*hit) = preStepPoint.GetKineticEnergy();
        Get<"p">(*hit) = preStepPoint.GetMomentum();
        Get<"TrkID">(*hit) = track.GetTrackID();
        Get<"PDGID">(*hit) = particle.GetPDGEncoding();
        Get<"t0">(*hit) = track.GetGlobalTime() - track.GetLocalTime();
        Get<"x0">(*hit) = track.GetVertexPosition();
        Get<"Ek0">(*hit) = vertexEk;
        Get<"p0">(*hit) = vertexMomentum;
        *Get<"CreatProc">(*hit) = creatorProcess ? std::string_view{creatorProcess->GetProcessName()} : "<0>";
        fHitsCollection->insert(hit);
    }
    return true;
}

auto MCPSD::EndOfEvent(G4HCofThisEvent*) -> void {
    Analysis::Instance().SubmitMCPHC(*fHitsCollection->GetVector());
}

} // namespace MACE::SimMACE::inline SD
