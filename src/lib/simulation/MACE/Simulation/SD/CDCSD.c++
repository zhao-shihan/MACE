#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/External/gfx/timsort.hpp"
#include "MACE/Math/MidPoint.h++"
#include "MACE/Simulation/SD/CDCSD.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/VectorArithmeticOperator.h++"
#include "MACE/Utility/VectorCast.h++"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VProcess.hh"
#include "G4VTouchable.hh"

#include <cassert>
#include <cmath>
#include <string_view>
#include <unordered_set>
#include <utility>

namespace MACE::inline Simulation::inline SD {

using namespace LiteralUnit::Energy;

CDCSD::CDCSD(const G4String& sdName) :
    NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fIonizingEnergyDepositionThreshold{25_eV},
    fMinNHitForQualifiedTrack{},
    fMeanDriftVelocity{},
    fCellMap{},
    fSplitHit{},
    fHitsCollection{},
    fTrackData{},
    fMessengerRegister{this} {
    collectionName.emplace_back(sdName + "HC");

    const auto& cdc{Detector::Description::CDC::Instance()};
    fMinNHitForQualifiedTrack = cdc.NSenseLayerPerSuper() * cdc.NSuperLayer();
    fMeanDriftVelocity = cdc.MeanDriftVelocity();
    fCellMap = &cdc.CellMap();

    fSplitHit.reserve(fCellMap->size());
}

auto CDCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHitsCollection = new CDCHitCollection(SensitiveDetectorName, collectionName[0]);
    const auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);

    fTrackData.clear();
}

auto CDCSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step{*theStep};
    const auto eDep{step.GetTotalEnergyDeposit()};

    assert(0 <= step.GetNonIonizingEnergyDeposit());
    assert(step.GetNonIonizingEnergyDeposit() <= eDep);
    if (eDep - step.GetNonIonizingEnergyDeposit() < fIonizingEnergyDepositionThreshold) { return false; }

    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};
    const auto& preStepPoint{*step.GetPreStepPoint()};
    const auto& postStepPoint{*step.GetPostStepPoint()};
    const auto& touchable{*preStepPoint.GetTouchable()};
    const auto position{Math::MidPoint(preStepPoint.GetPosition(), postStepPoint.GetPosition())};
    // retrive wire position
    const auto cellID{touchable.GetReplicaNumber(1)};
    const auto& cellInfo{fCellMap->at(cellID)};
    assert(cellID == cellInfo.cellID);
    const auto xWire{VectorCast<G4TwoVector>(cellInfo.position)};
    const auto tWire{VectorCast<G4ThreeVector>(cellInfo.direction)};
    // calculate drift distance
    const auto commonNormal{tWire.cross(Math::MidPoint(preStepPoint.GetMomentum(), postStepPoint.GetMomentum()))};
    const auto driftDistance{std::abs((position - xWire).dot(commonNormal)) / commonNormal.mag()};
    const auto driftTime{driftDistance / fMeanDriftVelocity};
    const auto hitTime{Math::MidPoint(preStepPoint.GetGlobalTime(), postStepPoint.GetGlobalTime())};
    const auto signalTime{hitTime + driftTime};
    // vertex Ek and p
    const auto vertexEk{track.GetVertexKineticEnergy()};
    const auto vertexMomentum{track.GetVertexMomentumDirection() * std::sqrt(vertexEk * (vertexEk + 2 * particle.GetPDGMass()))};
    // track creator process
    const auto creatorProcess{track.GetCreatorProcess()};
    // new a hit
    auto hit{std::make_unique_for_overwrite<CDCHit>()};
    Get<"EvtID">(*hit) = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    Get<"HitID">(*hit) = -1; // to be determined
    Get<"CellID">(*hit) = cellID;
    Get<"t">(*hit) = signalTime;
    Get<"tD">(*hit) = driftTime;
    Get<"d">(*hit) = driftDistance;
    Get<"Edep">(*hit) = eDep;
    Get<"tHit">(*hit) = hitTime;
    Get<"x">(*hit) = position;
    Get<"Ek">(*hit) = preStepPoint.GetKineticEnergy();
    Get<"p">(*hit) = preStepPoint.GetMomentum();
    Get<"TrkID">(*hit) = track.GetTrackID();
    Get<"PDGID">(*hit) = particle.GetPDGEncoding();
    Get<"t0">(*hit) = track.GetGlobalTime() - track.GetLocalTime();
    Get<"x0">(*hit) = track.GetVertexPosition();
    Get<"Ek0">(*hit) = vertexEk;
    Get<"p0">(*hit) = vertexMomentum;
    *Get<"CreatProc">(*hit) = creatorProcess ? std::string_view{creatorProcess->GetProcessName()} : "|0>";
    fSplitHit[cellID].emplace_back(std::move(hit));

    return true;
}

auto CDCSD::EndOfEvent(G4HCofThisEvent*) -> void {
    BuildHitData();
    BuildTrackData();
}

auto CDCSD::BuildHitData() -> void {
    for (int hitID{};
         auto&& [cellID, splitHit] : fSplitHit) {
        switch (splitHit.size()) {
        case 0:
            break;
        case 1: {
            auto& hit{splitHit.front()};
            Get<"HitID">(*hit) = hitID++;
            assert(Get<"CellID">(*hit) == cellID);
            fHitsCollection->insert(hit.release());
        } break;
        default: {
            const auto timeResolutionFWHM{Detector::Description::CDC::Instance().TimeResolutionFWHM()};
            // sort hit by signal time
            gfx::timsort(splitHit,
                         [](const auto& hit1, const auto& hit2) {
                             return Get<"t">(*hit1) < Get<"t">(*hit2);
                         });
            // loop over all hits on this cell and cluster to real hits by signal times
            std::vector<std::unique_ptr<CDCHit>*> hitCandidate;
            const auto ClusterAndInsertHit{
                [&] {
                    // find top hit
                    const auto iTopHit{std::ranges::min_element(std::as_const(hitCandidate),
                                                                [](const auto& hit1, const auto& hit2) {
                                                                    return Get<"TrkID">(**hit1) < Get<"TrkID">(**hit2);
                                                                })};
                    const auto topHit{*iTopHit};
                    // construct real hit
                    Get<"HitID">(**topHit) = hitID++;
                    assert(Get<"CellID">(**topHit) == cellID);
                    int nTopHit{};
                    for (auto&& hit : std::as_const(hitCandidate)) {
                        if (hit == topHit) { continue; }
                        Get<"Edep">(**topHit) += Get<"Edep">(**hit); // sum
                        if (Get<"TrkID">(**hit) == Get<"TrkID">(**topHit)) {
                            ++nTopHit;
                            Get<"tHit">(**topHit) += Get<"tHit">(**hit); // mean
                            *Get<"x">(**topHit) += *Get<"x">(**hit);     // mean
                        }
                    }
                    Get<"tHit">(**topHit) /= nTopHit; // mean
                    *Get<"x">(**topHit) /= nTopHit;   // mean
                    fHitsCollection->insert(topHit->release());
                }};
            for (auto windowClosingTime{Get<"t">(*splitHit.front()) + timeResolutionFWHM};
                 auto&& aSplitHit : splitHit) {
                if (Get<"t">(*aSplitHit) > windowClosingTime) {
                    ClusterAndInsertHit();
                    hitCandidate.clear();
                    windowClosingTime = Get<"t">(*aSplitHit) + timeResolutionFWHM;
                }
                hitCandidate.emplace_back(&aSplitHit);
            }
            ClusterAndInsertHit();
        } break;
        }
        splitHit.clear();
    }
}

auto CDCSD::BuildTrackData() -> void {
    auto& hitData{*fHitsCollection->GetVector()};
    gfx::timsort(hitData,
                 [](const auto& hit1, const auto& hit2) {
                     return Get<"TrkID">(*hit1) < Get<"TrkID">(*hit2);
                 });
    const auto magneticFluxDensity{Detector::Description::MMSField::Instance().MagneticFluxDensity()};
    auto lastTrackID{-1};
    std::unique_ptr<Data::Tuple<Data::MMSSimTrack>> track;
    std::unordered_set<int> firedCell;
    for (auto&& pHit : std::as_const(hitData)) {
        const auto& hit{*pHit};
        assert(Get<"TrkID">(hit) >= 0);
        if (Get<"TrkID">(hit) != lastTrackID) {
            lastTrackID = Get<"TrkID">(hit);
            if (track and ssize(firedCell) >= fMinNHitForQualifiedTrack) { fTrackData.emplace_back(std::move(track)); }
            track = std::make_unique_for_overwrite<Data::Tuple<Data::MMSSimTrack>>();
            Get<"EvtID">(*track) = Get<"EvtID">(hit);
            Get<"TrkID">(*track) = Get<"TrkID">(hit);
            Get<"chi2">(*track) = 0;
            Get<"t0">(*track) = Get<"t0">(hit);
            Get<"PDGID">(*track) = Get<"PDGID">(hit);
            Get<"x0">(*track) = Get<"x0">(hit);
            Get<"Ek0">(*track) = Get<"Ek0">(hit);
            Get<"p0">(*track) = Get<"p0">(hit);
            Data::CalculateHelix(*track, magneticFluxDensity);
            Get<"CreatProc">(*track) = Get<"CreatProc">(hit);
            firedCell.clear();
        }
        Get<"HitID">(*track)->emplace_back(Get<"HitID">(hit));
        firedCell.emplace(Get<"CellID">(hit));
    }
    if (track and ssize(firedCell) >= fMinNHitForQualifiedTrack) { fTrackData.emplace_back(std::move(track)); }
}

} // namespace MACE::inline Simulation::inline SD
