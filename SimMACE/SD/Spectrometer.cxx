#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4Tubs.hh"

#include "SimMACE/SD/Spectrometer.hxx"
#include "SimMACE/Analysis.hxx"

using namespace MACE::SimMACE;

SD::Spectrometer::Spectrometer(const G4String& SDName, const G4String& hitsCollectionName, const Geometry::Entity::Fast::SpectrometerCells* spectrometerCellEntity) :
    G4VSensitiveDetector(SDName),
    fHitsCollection(nullptr),
    fSpectrometerCellEntity(spectrometerCellEntity),
    fMonitoringTrackList(0) {
    collectionName.insert(hitsCollectionName);
}

SD::Spectrometer::~Spectrometer() {}

void SD::Spectrometer::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new Hit::SpectrometerHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool SD::Spectrometer::ProcessHits(G4Step* step, G4TouchableHistory*) {
    if (!(step->IsFirstStepInVolume() or step->IsLastStepInVolume())) { return false; }
    const auto* const track = step->GetTrack();
    const auto* const particle = track->GetDefinition();
    auto monitoring = FindMonitoring(track);
    auto isMonitoring = (monitoring != fMonitoringTrackList.cend());
    if (!isMonitoring and step->IsFirstStepInVolume() and track->GetCurrentStepNumber() > 1 and particle->GetPDGCharge() != 0) {
        const auto* const preStepPoint = step->GetPreStepPoint();
        fMonitoringTrackList.emplace_back(track, preStepPoint->GetGlobalTime(), preStepPoint->GetPosition());
        monitoring = std::prev(fMonitoringTrackList.cend());
        isMonitoring = true;
    }
    G4bool hasNewHit = false;
    if (isMonitoring and step->IsLastStepInVolume()) {
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
        // retrive cell info
        const auto* const touchable = step->GetPreStepPoint()->GetTouchable();
        const auto* const solidCell = static_cast<const G4Tubs*>(touchable->GetSolid());
        const auto cellHalfWidth = (solidCell->GetOuterRadius() - solidCell->GetInnerRadius()) / 2;
        auto cellId = touchable->GetCopyNumber();
        const auto& [layerId, cellPosition] = fSpectrometerCellEntity->GetLayerIdAndPosition(cellId);
        const auto& cellXc = cellPosition.x();
        const auto& cellYc = cellPosition.y();
        // calculate drift distance
        const auto driftDistance = std::fabs((inX - cellXc) * (outY - cellYc) - (outX - cellXc) * (inY - cellYc)) / hypot(outX - inX, outY - inY);
        if (driftDistance < cellHalfWidth) {
            // if drift distance exceeds threshold, new a hit
            auto* const hit = new Hit::SpectrometerHit();
            hit->SetHitTime((inT + outT) / 2);
            hit->SetWirePosition(cellXc, cellYc);
            hit->SetDriftDistance(driftDistance);
            hit->SetHitPositionZ((inZ + outZ) / 2);
            hit->SetCellID(cellId);
            hit->SetLayerID(layerId);
            hit->SetVertexTime(track->GetGlobalTime() - track->GetLocalTime());
            hit->SetVertexPosition(track->GetVertexPosition());
            hit->SetPDGCode(particle->GetPDGEncoding());
            hit->SetTrackID(track->GetTrackID());
            fHitsCollection->insert(hit);
            hasNewHit = true;
        }
        // particle exited, remove it from queue
        fMonitoringTrackList.erase(monitoring);
    }
    return hasNewHit;
}

void SD::Spectrometer::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance()->SubmitSpectrometerHC(fHitsCollection->GetVector());
}
