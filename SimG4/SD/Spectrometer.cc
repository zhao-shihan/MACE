#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4Tubs.hh"

#include "SimG4/SD/Spectrometer.hh"
#include "SimG4/Analysis.hh"

using namespace MACE::SimG4;

SD::Spectrometer::Spectrometer(const G4String& SDName, const G4String& hitsCollectionName) :
    G4VSensitiveDetector(SDName),
    fHitsCollection(nullptr),
    fCurrentTrack(nullptr),
    fInX(0.0),
    fInY(0.0) {
    collectionName.insert(hitsCollectionName);
    if (Hit::SpectrometerHitAllocator == nullptr) {
        Hit::SpectrometerHitAllocator = new G4Allocator<Hit::SpectrometerHit>();
    }
}

SD::Spectrometer::~Spectrometer() {}

void SD::Spectrometer::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new Hit::SpectrometerHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool SD::Spectrometer::ProcessHits(G4Step* step, G4TouchableHistory*) {
    const auto* const track = step->GetTrack();
    const auto* const particle = track->GetDefinition();
    if (step->IsFirstStepInVolume() && track->GetCurrentStepNumber() > 1 && particle->GetPDGCharge() != 0 && track != fCurrentTrack) {
        fCurrentTrack = track;
        const auto* const preStepPoint = step->GetPreStepPoint();
        fInX = preStepPoint->GetPosition().x();
        fInY = preStepPoint->GetPosition().y();
        return true;
    }
    if (step->IsLastStepInVolume() && track == fCurrentTrack) {
        fCurrentTrack = nullptr;
        const auto* const postStepPoint = step->GetPostStepPoint();
        const auto outX = postStepPoint->GetPosition().x();
        const auto outY = postStepPoint->GetPosition().y();
        const auto* const touchable = step->GetPreStepPoint()->GetTouchable();
        const auto* const solidCell = static_cast<const G4Tubs*>(touchable->GetSolid());
        const auto cellCenterRadius = (solidCell->GetInnerRadius() + solidCell->GetOuterRadius()) / 2;
        const auto* const cellRotation = touchable->GetRotation();
        const auto cellCenterPhi = ((cellRotation->getAxis().z() > 0) ? (-cellRotation->getDelta()) : (cellRotation->getDelta())) + solidCell->GetStartPhiAngle() + solidCell->GetDeltaPhiAngle() / 2;
        const auto centerX = cellCenterRadius * cos(cellCenterPhi);
        const auto centerY = cellCenterRadius * sin(cellCenterPhi);
        auto* const hit = new Hit::SpectrometerHit();
        hit->SetHitTime(postStepPoint->GetGlobalTime());
        hit->SetWirePosition(centerX, centerY);
        hit->SetDriftDistance(fabs((fInX - centerX) * (outY - centerY) - (outX - centerX) * (fInY - centerY)) / hypot(outX - fInX, outY - fInY));
        hit->SetHitPositionZ(step->GetPreStepPoint()->GetPosition().z());
        hit->SetCellID(touchable->GetCopyNumber());
        hit->SetVertexTime(track->GetGlobalTime() - track->GetLocalTime());
        hit->SetVertexPosition(track->GetVertexPosition());
        hit->SetPDGCode(particle->GetPDGEncoding());
        hit->SetTrackID(track->GetTrackID());
        fHitsCollection->insert(hit);
        return true;
    }
    return false;
}

void SD::Spectrometer::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance()->SubmitSpectrometerHC(fHitsCollection->GetVector());
}
