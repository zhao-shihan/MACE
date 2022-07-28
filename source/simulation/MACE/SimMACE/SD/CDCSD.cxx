#include "MACE/Core/Geometry/Description/CDC.hxx"
#include "MACE/SimMACE/Region.hxx"
#include "MACE/SimMACE/RunManager.hxx"
#include "MACE/SimMACE/SD/CDCSD.hxx"

#include "G4HCofThisEvent.hh"
#include "G4ProductionCuts.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

namespace MACE::SimMACE::SD {

using Hit::CDCHit;

CDCSD::CDCSD(const G4String& sdName) :
    NonMoveableBase(),
    G4VSensitiveDetector(sdName),
    fEventID(-1),
    fHitsCollection(nullptr),
    fEnteredPointList(),
    fSenseWireMap(0) {

    collectionName.insert(sdName + "HC");

    const auto senseWireMap = Core::Geometry::Description::CDC::Instance().SenseWireMap();
    fSenseWireMap.resize(senseWireMap.size());
    for (size_t i = 0; i < senseWireMap.size(); ++i) {
        auto& [wirePosG4, wireDirG4] = fSenseWireMap[i];
        const auto& [wirePosEigen, wireDirEigen] = senseWireMap[i];
        wirePosG4.set(wirePosEigen.x(), wirePosEigen.y());
        wireDirG4.set(wireDirEigen.x(), wireDirEigen.y(), wireDirEigen.z());
    }
}

void CDCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new CDCHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool CDCSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    if (!step->IsFirstStepInVolume() and !step->IsLastStepInVolume()) { return false; }
    const auto* const track = step->GetTrack();
    const auto* const particle = track->GetDefinition();
    if (track->GetCurrentStepNumber() <= 1 or particle->GetPDGCharge() == 0) { return false; }
    // get track ID and cell ID of this hit
    const auto trackID = track->GetTrackID();
    const auto* const touchable = track->GetTouchable();
    const auto cellID = touchable->GetReplicaNumber(1);
    // find entered point
    auto monitoring = std::as_const(fEnteredPointList).find({trackID, cellID});
    auto isMonitoring = (monitoring != fEnteredPointList.cend());
    if (!isMonitoring and step->IsFirstStepInVolume()) { // is first time entering.
        monitoring = fEnteredPointList.emplace(std::make_pair(trackID, cellID), *step->GetPostStepPoint()).first;
        isMonitoring = true;
    }
    if (isMonitoring and step->IsLastStepInVolume() and                                                                         // is exiting, and make sure has entered before,
        static_cast<Region*>(track->GetNextVolume()->GetLogicalVolume()->GetRegion())->GetType() != RegionType::DefaultSolid) { // but the track is not heading into sense wire!
        // retrive layerID
        const auto layerID = touchable->GetReplicaNumber(2);
        // retrive entering time and position
        const auto& enterPoint = monitoring->second;
        const auto tIn = enterPoint.GetGlobalTime();
        const auto rIn = enterPoint.GetPosition();
        const auto pIn = enterPoint.GetMomentumDirection();
        const auto zIn = enterPoint.GetPosition().z();
        // retrive exiting time and position
        const auto* const exitPoint = step->GetPreStepPoint();
        const auto tOut = exitPoint->GetGlobalTime();
        const auto rOut = exitPoint->GetPosition();
        const auto pOut = exitPoint->GetMomentumDirection();
        const auto zOut = exitPoint->GetPosition().z();
        // retrive wire position
        const auto& [rWire, tWire] = fSenseWireMap[cellID];
        // calculate drift distance
        const auto commonNormalVector = tWire.cross((pIn + pOut) / 2);
        const auto driftDistance = std::abs(((rIn + rOut) / 2 - rWire).dot(commonNormalVector) / commonNormalVector.mag());
        // calculate vertex energy and momentum
        const auto vertexTotalEnergy = track->GetVertexKineticEnergy() + particle->GetPDGMass();
        const auto vertexMomentum = track->GetVertexMomentumDirection() * std::sqrt(track->GetVertexKineticEnergy() * (vertexTotalEnergy + particle->GetPDGMass()));
        // new a hit
        auto* const hit = new CDCHit();
        hit->SetHitTime((tIn + tOut) / 2);
        hit->SetDriftDistance(driftDistance);
        hit->SetHitPositionZ((zIn + zOut) / 2);
        hit->SetWirePosition(rWire);
        hit->SetWireDirection(tWire);
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
        hit->SetG4TrackID(trackID);
        fHitsCollection->insert(hit);
        // particle is exiting, remove it from monitoring list
        fEnteredPointList.erase(monitoring);
        return true;
    }
    return false;
}

void CDCSD::EndOfEvent(G4HCofThisEvent*) {
    RunManager::Instance().GetAnalysis().SubmitSpectrometerHC(fHitsCollection->GetVector());
    fEnteredPointList.clear();
}

} // namespace MACE::SimMACE::SD
