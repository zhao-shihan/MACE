#include "MACE/Core/Geometry/Description/CDC.hxx"
#include "MACE/SimMACE/Region.hxx"
#include "MACE/SimMACE/RunManager.hxx"
#include "MACE/SimMACE/SD/CDCSD.hxx"
#include "MACE/Utility/VectorCast.hxx"

#include "G4HCofThisEvent.hh"
#include "G4ProductionCuts.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

#include "gsl/gsl"

namespace MACE::SimMACE::SD {

using Hit::CDCHit;

CDCSD::CDCSD(const G4String& sdName) :
    NonMoveableBase(),
    G4VSensitiveDetector(sdName),
    fEventID(-1),
    fHitsCollection(nullptr),
    fEnteredPointList(),
    fCellMap() {

    collectionName.insert(sdName + "HC");

    const auto cellMap = Core::Geometry::Description::CDC::Instance().CellMap();
    fCellMap.reserve(cellMap.size());
    for (auto&& cell : cellMap) {
        fCellMap.emplace_back(Utility::VectorCast<G4TwoVector, 2>(cell.position),
                              Utility::VectorCast<G4ThreeVector, 3>(cell.direction));
    }
}

void CDCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new CDCHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool CDCSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    if (not(step->IsFirstStepInVolume() or step->IsLastStepInVolume())) { return false; }
    const auto track = step->GetTrack();
    const auto particle = track->GetDefinition();
    if (track->GetCurrentStepNumber() <= 1 or particle->GetPDGCharge() == 0) { return false; }
    // get track ID and cell ID of this hit
    const auto trackID = track->GetTrackID();
    const auto touchable = track->GetTouchable();
    const auto cellID = touchable->GetReplicaNumber();
    // find entered point
    const auto [monitoring, isNew] = fEnteredPointList.try_emplace({trackID, cellID}, *step->GetPostStepPoint());
    if (not isNew and step->IsLastStepInVolume() and                                                                            // is exiting, and make sure has entered before,
        static_cast<Region*>(track->GetNextVolume()->GetLogicalVolume()->GetRegion())->GetType() != RegionType::DefaultSolid) { // but the track is not heading into sense wire!
        // retrive entering time and position
        const auto& enterPoint = monitoring->second;
        const auto tIn = enterPoint.GetGlobalTime();
        const auto rIn = enterPoint.GetPosition();
        const auto pIn = enterPoint.GetMomentumDirection();
        // retrive exiting time and position
        const auto exitPoint = step->GetPreStepPoint();
        const auto tOut = exitPoint->GetGlobalTime();
        const auto rOut = exitPoint->GetPosition();
        const auto pOut = exitPoint->GetMomentumDirection();
        // retrive wire position
        const auto& [rWire, tWire] = fCellMap[cellID];
        // calculate drift distance
        const auto commonNormalVector = tWire.cross((pIn + pOut) / 2);
        const auto driftDistance = std::abs(((rIn + rOut) / 2 - rWire).dot(commonNormalVector) / commonNormalVector.mag());
        // calculate vertex energy and momentum
        const auto vertexTotalEnergy = track->GetVertexKineticEnergy() + particle->GetPDGMass();
        const auto vertexMomentum = track->GetVertexMomentumDirection() * std::sqrt(track->GetVertexKineticEnergy() * (vertexTotalEnergy + particle->GetPDGMass()));
        // new a hit
        const auto hit = new CDCHit;
        hit->HitTime((tIn + tOut) / 2);
        hit->DriftDistance(driftDistance);
        hit->CellID(cellID);
        hit->Energy((enterPoint.GetTotalEnergy() + exitPoint->GetTotalEnergy()) / 2);
        hit->Momentum((enterPoint.GetMomentum() + exitPoint->GetMomentum()) / 2);
        hit->VertexTime(track->GetGlobalTime() - track->GetLocalTime());
        hit->VertexPosition(track->GetVertexPosition());
        hit->VertexEnergy(vertexTotalEnergy);
        hit->VertexMomentum(vertexMomentum);
        hit->Particle(particle->GetParticleName());
        hit->G4EventID(fEventID);
        hit->G4TrackID(trackID);
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
