#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4Tubs.hh"

#include "SimMACE/SD/Spectrometer.hxx"
#include "SimMACE/Analysis.hxx"

using namespace MACE::SimMACE;

SD::Spectrometer::Spectrometer(const G4String& SDName, const G4String& hitsCollectionName) :
    G4VSensitiveDetector(SDName),
    fHitsCollection(nullptr),
    fMonitoringTrackList(0) {
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
    if (!(step->IsFirstStepInVolume() || step->IsLastStepInVolume())) { return false; }
    const auto* const track = step->GetTrack();
    const auto* const particle = track->GetDefinition();
    auto monitoring = FindMonitoring(track);
    auto isMonitoring = (monitoring != fMonitoringTrackList.cend());
    const auto isEntering = step->IsFirstStepInVolume() && track->GetCurrentStepNumber() > 1 && particle->GetPDGCharge() != 0 && !isMonitoring;
    if (isEntering) {
        const auto* const preStepPoint = step->GetPreStepPoint();
        fMonitoringTrackList.emplace_back(track, preStepPoint->GetGlobalTime(), preStepPoint->GetPosition());
        monitoring = std::prev(fMonitoringTrackList.cend());
        isMonitoring = true;
    }
    const auto isExiting = step->IsLastStepInVolume() && isMonitoring;
    if (isExiting) {
        // retrive entering time and position
        const auto inT = std::get<1>(*monitoring);
        const auto inX = std::get<2>(*monitoring).x();
        const auto inY = std::get<2>(*monitoring).y();
        const auto inZ = std::get<2>(*monitoring).z();
        // retrive exiting time and position
        const auto* const postStepPoint = step->GetPostStepPoint();
        const auto outT = postStepPoint->GetGlobalTime();
        const auto outX = postStepPoint->GetPosition().x();
        const auto outY = postStepPoint->GetPosition().y();
        const auto outZ = postStepPoint->GetPosition().z();
        // calculate cell center
        const auto* const touchable = step->GetPreStepPoint()->GetTouchable();
        const auto* const solidCell = static_cast<const G4Tubs*>(touchable->GetSolid());
        const auto cellCenterRadius = (solidCell->GetInnerRadius() + solidCell->GetOuterRadius()) / 2;
        const auto* const cellRotation = touchable->GetRotation();
        const auto cellCenterPhi = ((cellRotation->getAxis().z() > 0) ? (-cellRotation->getDelta()) : (cellRotation->getDelta())) + solidCell->GetStartPhiAngle() + solidCell->GetDeltaPhiAngle() / 2;
        const auto centerX = cellCenterRadius * cos(cellCenterPhi);
        const auto centerY = cellCenterRadius * sin(cellCenterPhi);
        // new a hit
        auto* const hit = new Hit::SpectrometerHit();
        hit->SetHitTime((inT + outT) / 2);
        hit->SetWirePosition(centerX, centerY);
        hit->SetDriftDistance(std::fabs((inX - centerX) * (outY - centerY) - (outX - centerX) * (inY - centerY)) / hypot(outX - inX, outY - inY));
        hit->SetHitPositionZ((inZ + outZ) / 2);
        hit->SetCellID(touchable->GetCopyNumber());
        hit->SetVertexTime(track->GetGlobalTime() - track->GetLocalTime());
        hit->SetVertexPosition(track->GetVertexPosition());
        hit->SetPDGCode(particle->GetPDGEncoding());
        hit->SetTrackID(track->GetTrackID());
        fHitsCollection->insert(hit);
        // particle exited, remove it from queue
        fMonitoringTrackList.erase(monitoring);
    }
    return isEntering || isExiting;
}

void SD::Spectrometer::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance()->SubmitSpectrometerHC(fHitsCollection->GetVector());
}
