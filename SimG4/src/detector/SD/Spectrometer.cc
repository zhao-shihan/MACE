#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "g4analysis.hh"

#include "detector/SD/Spectrometer.hh"

using namespace MACE::SimG4::SD;
using namespace MACE::SimG4::Hit;

Spectrometer::Spectrometer(const G4String& SDName, const G4String& hitsCollectionName) :
    G4VSensitiveDetector(SDName),
    fHitsCollection(nullptr) {
    collectionName.insert(hitsCollectionName);
    if (SpectrometerHitAllocator == nullptr) {
        SpectrometerHitAllocator = new G4Allocator<SpectrometerHit>();
    }
}

Spectrometer::~Spectrometer() {}

void Spectrometer::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new SpectrometerHitsCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool Spectrometer::ProcessHits(G4Step* step, G4TouchableHistory*) {
    const auto* const track = step->GetTrack();
    if (!(step->IsFirstStepInVolume() && track->GetCurrentStepNumber() > 1 &&
        track->GetDefinition()->GetPDGCharge() != 0)) {
        return false;
    }
    const auto* const preStepPoint = step->GetPreStepPoint();
    fHitsCollection->insert(
        new SpectrometerHit(
            track->GetTrackID(),
            preStepPoint->GetTouchable()->GetCopyNumber(),
            track->GetGlobalTime() - track->GetLocalTime(),
            track->GetVertexPosition(),
            preStepPoint->GetGlobalTime(),
            preStepPoint->GetPosition()
        )
    );
    return true;
}

void Spectrometer::EndOfEvent(G4HCofThisEvent*) {
    auto* const analysis = G4AnalysisManager::Instance();
    for (size_t i = 0; i < fHitsCollection->GetSize(); ++i) {
        const auto* const hit = static_cast<SpectrometerHit*>(fHitsCollection->GetHit(i));
        constexpr G4int ntupleID = 2;
        analysis->FillNtupleIColumn(ntupleID, 0, hit->TrackID);
        analysis->FillNtupleIColumn(ntupleID, 1, hit->ChamberID);
        analysis->FillNtupleFColumn(ntupleID, 2, hit->VertexTime);
        analysis->FillNtupleFColumn(ntupleID, 3, hit->VertexPosition.x());
        analysis->FillNtupleFColumn(ntupleID, 4, hit->VertexPosition.y());
        analysis->FillNtupleFColumn(ntupleID, 5, hit->VertexPosition.z());
        analysis->FillNtupleFColumn(ntupleID, 6, hit->HitTime);
        analysis->FillNtupleFColumn(ntupleID, 7, hit->HitPosition.x());
        analysis->FillNtupleFColumn(ntupleID, 8, hit->HitPosition.y());
        analysis->FillNtupleFColumn(ntupleID, 9, hit->HitPosition.z());
        analysis->AddNtupleRow(ntupleID);
    }
}
