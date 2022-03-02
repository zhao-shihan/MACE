#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4Tubs.hh"

#include "SimMACE/SD/SpectrometerSD.hxx"
#include "SimMACE/Utility/Analysis.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/DescendantsOfSpectrometerCells/SpectrometerSensitiveVolumes.hxx"

using namespace MACE::SimMACE::SD;

SpectrometerSD::SpectrometerSD(const G4String& SDName, const G4String& hitsCollectionName) :
    G4VSensitiveDetector(SDName),
    fHitsCollection(nullptr),
    fMonitoringTrackList(0),
    fSpectrometerSensitiveVolumeInfoList(Geometry::Description::SpectrometerSensitiveVolumes::Instance().GetInformationList()) {
    collectionName.insert(hitsCollectionName);
}

void SpectrometerSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new SpectrometerHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool SpectrometerSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    if (!step->IsFirstStepInVolume() and !step->IsLastStepInVolume()) { return false; }
    const auto* const track = step->GetTrack();
    const auto* const particle = track->GetDefinition();
    if (track->GetCurrentStepNumber() <= 1 or particle->GetPDGCharge() == 0) { return false; }
    auto monitoring = FindMonitoring(track);
    auto isMonitoring = (monitoring != fMonitoringTrackList.cend());
    if (!isMonitoring and step->IsFirstStepInVolume()) {
        const auto* const preStepPoint = step->GetPreStepPoint();
        fMonitoringTrackList.emplace_back(track, preStepPoint->GetGlobalTime(), preStepPoint->GetPosition());
        monitoring = std::prev(fMonitoringTrackList.cend());
        isMonitoring = true;
    }
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
        auto cellID = step->GetPreStepPoint()->GetTouchable()->GetCopyNumber();
        const auto& [layerID, _, wirePosition] = fSpectrometerSensitiveVolumeInfoList[cellID];
        const auto wireX = wirePosition.x();
        const auto wireY = wirePosition.y();
        // calculate drift distance
        const auto driftDistance = std::fabs((inX - wireX) * (outY - wireY) - (outX - wireX) * (inY - wireY)) / std::hypot(outX - inX, outY - inY);
        auto* const hit = new SpectrometerHit();
        hit->SetHitTime((inT + outT) / 2);
        hit->SetWirePosition(wireX, wireY);
        hit->SetDriftDistance(driftDistance);
        hit->SetHitPositionZ((inZ + outZ) / 2);
        hit->SetCellID(cellID);
        hit->SetLayerID(layerID);
        hit->SetVertexTime(track->GetGlobalTime() - track->GetLocalTime());
        hit->SetVertexPosition(track->GetVertexPosition());
        hit->SetPDGCode(particle->GetPDGEncoding());
        hit->SetTrackID(track->GetTrackID());
        fHitsCollection->insert(hit);
        // particle exited, remove it from monitoring list
        fMonitoringTrackList.erase(monitoring);
        return true;
    }
    return false;
}

void SpectrometerSD::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance().SubmitSpectrometerHC(fHitsCollection->GetVector());
}
