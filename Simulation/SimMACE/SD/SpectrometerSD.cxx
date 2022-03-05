#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4Tubs.hh"

#include "SimMACE/SD/SpectrometerSD.hxx"
#include "SimMACE/RunManager.hxx"
#include "SimMACE/Utility/Analysis.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/SpectrometerCells.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/DescendantsOfSpectrometerCells/SpectrometerSensitiveVolumes.hxx"

using namespace MACE::SimMACE::SD;

SpectrometerSD::SpectrometerSD(const G4String& sdName) :
    G4VSensitiveDetector(sdName),
    fHitsCollection(nullptr),
    fMonitoringTrackList(0),
    fSenseWireMap(0) {

    collectionName.insert(sdName + "HC");

    const auto cellInfoList = Geometry::Description::SpectrometerCells::Instance().GetInformationList();
    const auto svInfoList = Geometry::Description::SpectrometerSensitiveVolumes::Instance().GetInformationList();
    const auto layerCount = cellInfoList.size();
    fSenseWireMap.reserve(3 * layerCount * layerCount); // just an estimation of cell count (pi*r^2), for optimization.
    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        auto&& localPosition = std::get<2>(svInfoList[layerID]);
        for (auto&& rotation : std::get<2>(cellInfoList[layerID])) {
            fSenseWireMap.emplace_back(rotation * localPosition);
        }
    }
    fSenseWireMap.shrink_to_fit();
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
        fMonitoringTrackList.emplace_back(track, step->GetPreStepPoint());
        monitoring = std::prev(fMonitoringTrackList.cend());
        isMonitoring = true;
    }
    if (isMonitoring and step->IsLastStepInVolume()) {
        // retrive entering time and position
        const auto& enterPoint = monitoring->second;
        const auto tIn = enterPoint->GetGlobalTime();
        const auto rIn = G4TwoVector(enterPoint->GetPosition());
        const auto zIn = enterPoint->GetPosition().z();
        // retrive exiting time and position
        const auto* const exitPoint = step->GetPostStepPoint();
        const auto tOut = exitPoint->GetGlobalTime();
        const auto rOut = G4TwoVector(exitPoint->GetPosition());
        const auto zOut = exitPoint->GetPosition().z();
        // retrive cellID and layerID
        const auto* const svTouchable = track->GetTouchable();
        const auto cellID = svTouchable->GetReplicaNumber(1);
        const auto layerID = svTouchable->GetReplicaNumber(2);
        // retrive wire position
        const auto& rWire = fSenseWireMap[cellID];
        // calculate drift distance
        const auto driftDistance = ((rIn - rWire) + (rOut - rWire)).mag() / 2;
        // new a hit
        auto* const hit = new SpectrometerHit();
        hit->SetHitTime((tIn + tOut) / 2);
        hit->SetWirePosition(rWire);
        hit->SetDriftDistance(driftDistance);
        hit->SetHitPositionZ((zIn + zOut) / 2);
        hit->SetCellID(cellID);
        hit->SetLayerID(layerID);
        hit->SetMomentum((enterPoint->GetMomentum() + exitPoint->GetMomentum()) / 2);
        hit->SetVertexTime(track->GetGlobalTime() - track->GetLocalTime());
        hit->SetVertexPosition(track->GetVertexPosition());
        hit->SetPDGCode(particle->GetPDGEncoding());
        hit->SetEventID(fEventID);
        hit->SetTrackID(track->GetTrackID());
        fHitsCollection->insert(hit);
        // particle is exiting, remove it from monitoring list
        fMonitoringTrackList.erase(monitoring);
        return true;
    }
    return false;
}

void SpectrometerSD::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance().SubmitSpectrometerHC(fHitsCollection->GetVector());
}
