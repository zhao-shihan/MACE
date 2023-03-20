#include "MACE/Detector/Description/CDC.hxx"
#include "MACE/Math/MidPoint.hxx"
#include "MACE/SimMACE/Analysis.hxx"
#include "MACE/SimMACE/Region.hxx"
#include "MACE/SimMACE/SD/CDCSD.hxx"
#include "MACE/Utility/VectorCast.hxx"

#include "G4HCofThisEvent.hh"
#include "G4ProductionCuts.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

#include "gsl/gsl"

#include <algorithm>
#include <numeric>

namespace MACE::SimMACE::inline SD {

CDCSD::CDCSD(const G4String& sdName) :
    NonMoveableBase(),
    G4VSensitiveDetector(sdName),
    fEventID(-1),
    fHitsCollection(nullptr),
    fMeanDriftVelocity(),
    fHalfTimeResolution(),
    fCellEntryPoints(),
    fCellMap(),
    fCellSignalTimesAndHits() {
    const auto& cellMap = Detector::Description::CDC::Instance().CellMap();
    fCellEntryPoints.resize(cellMap.size());
    fCellMap.reserve(cellMap.size());
    for (auto&& cell : cellMap) {
        fCellMap.emplace_back(VectorCast<G4TwoVector>(cell.position),
                              VectorCast<G4ThreeVector>(cell.direction));
    }
    fCellSignalTimesAndHits.resize(cellMap.size());

    collectionName.insert(sdName + "HC");
}

void CDCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new CDCHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);

    const auto& cdc = Detector::Description::CDC::Instance();
    fMeanDriftVelocity = cdc.MeanDriftVelocity();
    fHalfTimeResolution = cdc.TimeResolution() / 2;
}

G4bool CDCSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) {
    const auto& step = *theStep;
    const auto& track = *step.GetTrack();
    const auto& particle = *track.GetDefinition();

    if (track.GetCurrentStepNumber() <= 1 or particle.GetPDGCharge() == 0) {
        return false;
    }

    const auto trackID = track.GetTrackID();
    const auto& touchable = *track.GetTouchable();
    const auto cellID = touchable.GetReplicaNumber();
    auto& entryPointList = fCellEntryPoints[cellID];

    if (step.IsFirstStepInVolume()) {
        entryPointList.try_emplace(trackID, *step.GetPostStepPoint());
        return false;
    }

    const auto& nextReigon = static_cast<Region&>(*track.GetNextVolume()->GetLogicalVolume()->GetRegion());
    decltype(entryPointList.cbegin()) monitoring;
    if (step.IsLastStepInVolume() and                                           // is exiting,
        nextReigon.GetType() != RegionType::CDCSenseWire and                    // but the track is not heading into sense wire,
        (monitoring = entryPointList.find(trackID)) != entryPointList.cend()) { // and make sure it has entered before.
        // retrive entering time and position
        const auto& enterPoint = monitoring->second;
        const auto tIn = enterPoint.GetGlobalTime();
        const auto rIn = enterPoint.GetPosition();
        const auto pIn = enterPoint.GetMomentumDirection();
        // retrive exiting time and position
        const auto& exitPoint = *step.GetPreStepPoint();
        const auto tOut = exitPoint.GetGlobalTime();
        const auto rOut = exitPoint.GetPosition();
        const auto pOut = exitPoint.GetMomentumDirection();
        // retrive wire position
        const auto& [rWire, tWire] = fCellMap[cellID];
        // calculate drift distance
        const auto commonNormalVector = tWire.cross(Math::MidPoint(pIn, pOut));
        const auto driftDistance = std::abs((Math::MidPoint(rIn, rOut) - rWire).dot(commonNormalVector) / commonNormalVector.mag());
        // calculate vertex energy and momentum
        const auto vertexTotalEnergy = track.GetVertexKineticEnergy() + particle.GetPDGMass();
        const auto vertexMomentum = track.GetVertexMomentumDirection() * std::sqrt(track.GetVertexKineticEnergy() * (vertexTotalEnergy + particle.GetPDGMass()));
        // new a hit
        auto hit = std::make_unique_for_overwrite<CDCHit>();
        hit->HitTime(Math::MidPoint(tIn, tOut));
        hit->DriftDistance(driftDistance);
        hit->CellID(cellID);
        hit->Energy(Math::MidPoint(enterPoint.GetTotalEnergy(), exitPoint.GetTotalEnergy()));
        hit->Momentum(Math::MidPoint(enterPoint.GetMomentum(), exitPoint.GetMomentum()));
        hit->VertexTime(track.GetGlobalTime() - track.GetLocalTime());
        hit->VertexPosition(track.GetVertexPosition());
        hit->VertexEnergy(vertexTotalEnergy);
        hit->VertexMomentum(vertexMomentum);
        hit->Particle(particle.GetParticleName());
        hit->G4EventID(fEventID);
        hit->G4TrackID(trackID);
        fCellSignalTimesAndHits[cellID].emplace_back(hit->HitTime() + driftDistance / fMeanDriftVelocity,
                                                     std::move(hit));
        // particle is exiting, remove it from monitoring list
        entryPointList.erase(monitoring);
        return true;
    }

    return false;
}

void CDCSD::EndOfEvent(G4HCofThisEvent*) {
    for (auto&& entryPointList : fCellEntryPoints) {
        entryPointList.clear();
    }

    auto& hits = *fHitsCollection->GetVector();
    hits.reserve(
        std::accumulate(fCellSignalTimesAndHits.cbegin(), fCellSignalTimesAndHits.cend(), 0ull,
                        [](const auto& count, const auto& signalTimesAndHits) {
                            return count + signalTimesAndHits.size();
                        }));

    for (auto&& signalTimesAndHits : fCellSignalTimesAndHits) {
        if (signalTimesAndHits.empty()) { continue; }

        std::ranges::sort(signalTimesAndHits);

        std::vector<std::unique_ptr<CDCHit>*> signalHitCandidateList;
        auto signalTimeThreshold = signalTimesAndHits.front().first + fHalfTimeResolution;
        for (auto timeHit = signalTimesAndHits.begin(); timeHit != signalTimesAndHits.end(); ++timeHit) {
            signalHitCandidateList.emplace_back(&timeHit->second);
            const auto signalTime = timeHit->first;
            if (signalTime > signalTimeThreshold or timeHit == std::prev(signalTimesAndHits.end())) {
                const auto goodHit =
                    *std::ranges::max_element(signalHitCandidateList,
                                              [](const auto& hit1, const auto& hit2) {
                                                  return (*hit1)->Energy() < (*hit2)->Energy();
                                              });
                hits.emplace_back(goodHit->release());
                signalHitCandidateList.clear();
                signalTimeThreshold = signalTime + fHalfTimeResolution;
            }
        }

        signalTimesAndHits.clear();
    }

    Analysis::Instance().SubmitSpectrometerHC(&hits);
}

} // namespace MACE::SimMACE::inline SD
