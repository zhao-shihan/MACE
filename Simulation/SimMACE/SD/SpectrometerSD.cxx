#include "Core/Geometry/Description/SpectrometerCells.hxx"
#include "Core/Geometry/Description/SpectrometerSenseWires.hxx"
#include "Simulation/SimMACE/RunManager.hxx"
#include "Simulation/SimMACE/SD/SpectrometerSD.hxx"
#include "Simulation/SimMACE/Utility/Analysis.hxx"
#include "Simulation/SimMACE/Utility/Region.hxx"

#include "G4HCofThisEvent.hh"
#include "G4ProductionCuts.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

namespace MACE::Simulation::SimMACE::SD {

using Hit::SpectrometerHit;
using Utility::Analysis;

SpectrometerSD::SpectrometerSD(const G4String& sdName) :
    G4VSensitiveDetector(sdName),
    fHitsCollection(nullptr),
    fMonitoringTrackList(),
    fSenseWireMap(0) {

    collectionName.insert(sdName + "HC");

    const auto cellInfoList = Geometry::Description::SpectrometerCells::Instance().GetInformationList();
    const auto wireInfoList = Geometry::Description::SpectrometerSenseWires::Instance().GetInformationList();
    const auto layerCount = cellInfoList.size();
    fSenseWireMap.reserve(3 * layerCount * layerCount); // just an estimation of cell count (pi*r^2), for optimization.
    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        const auto& [wireLocalPosition, _3] = wireInfoList[layerID];
        for (auto&& rotation : std::get<2>(cellInfoList[layerID])) {
            fSenseWireMap.emplace_back(rotation * wireLocalPosition);
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
    auto monitoring = std::as_const(fMonitoringTrackList).find(track);
    auto isMonitoring = (monitoring != fMonitoringTrackList.cend());
    if (!isMonitoring and step->IsFirstStepInVolume()) { // is first time entering.
        fMonitoringTrackList.emplace(track, *step->GetPreStepPoint());
        monitoring = std::prev(fMonitoringTrackList.cend());
        isMonitoring = true;
    }
    if (isMonitoring and step->IsLastStepInVolume() and                                                                      // is exiting, and make sure has entered before,
        static_cast<Region*>(track->GetNextVolume()->GetLogicalVolume()->GetRegion())->GetType() != Region::kDefaultSolid) { // but not heading into sense wire!
        // retrive entering time and position
        const auto& enterPoint = monitoring->second;
        const auto tIn = enterPoint.GetGlobalTime();
        const auto rIn = G4TwoVector(enterPoint.GetPosition());
        const auto zIn = enterPoint.GetPosition().z();
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
        const auto r1 = rIn - rWire;
        const auto r2 = rOut - rWire;
        const auto driftDistance = std::abs(r1.x() * r2.y() - r2.x() * r1.y()) / (r1 - r2).mag();
        // calculate vertex energy and momentum
        const auto vertexTotalEnergy = track->GetVertexKineticEnergy() + particle->GetPDGMass();
        const auto vertexMomentum = track->GetVertexMomentumDirection() * std::sqrt(track->GetVertexKineticEnergy() * (vertexTotalEnergy + particle->GetPDGMass()));
        // new a hit
        auto* const hit = new SpectrometerHit();
        hit->SetHitTime((tIn + tOut) / 2);
        hit->SetWirePosition(rWire);
        hit->SetDriftDistance(driftDistance);
        hit->SetHitPositionZ((zIn + zOut) / 2);
        hit->SetCellID(cellID);
        hit->SetLayerID(layerID);
        hit->SetEnergy((enterPoint.GetTotalEnergy() + exitPoint->GetTotalEnergy()) / 2);
        hit->SetMomentum((enterPoint.GetMomentum() + exitPoint->GetMomentum()) / 2);
        hit->SetVertexTime(track->GetGlobalTime() - track->GetLocalTime());
        hit->SetVertexPosition(track->GetVertexPosition());
        hit->SetVertexEnergy(vertexTotalEnergy);
        hit->SetVertexMomentum(vertexMomentum);
        hit->SetParticle(particle->GetParticleName());
        hit->SetG4EventID(fEventID);
        hit->SetG4TrackID(track->GetTrackID());
        fHitsCollection->insert(hit);
        // particle is exiting, remove it from monitoring list
        fMonitoringTrackList.erase(monitoring);
        return true;
    }
    return false;
}

void SpectrometerSD::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance().SubmitSpectrometerHC(fHitsCollection->GetVector());
    fMonitoringTrackList.clear();
}

} // namespace MACE::Simulation::SimMACE::SD
