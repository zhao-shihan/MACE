#include "MACE/Compatibility/std23/unreachable.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Env/Print.h++"
#include "MACE/External/gfx/timsort.hpp"
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

#include "muc/numeric"

#include <cassert>
#include <cmath>
#include <ranges>
#include <string_view>
#include <utility>

namespace MACE::inline Simulation::inline SD {

using namespace LiteralUnit::Energy;

CDCSD::CDCSD(const G4String& sdName) :
    NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fIonizingEnergyDepositionThreshold{25_eV},
    fMeanDriftVelocity{},
    fCellMap{},
    fSplitHit{},
    fHitsCollection{},
    fMessengerRegister{this} {
    collectionName.emplace_back(sdName + "HC");

    const auto& cdc{Detector::Description::CDC::Instance()};
    fMeanDriftVelocity = cdc.MeanDriftVelocity();
    fCellMap = &cdc.CellMap();

    fSplitHit.reserve(fCellMap->size());
}

auto CDCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHitsCollection = new CDCHitCollection{SensitiveDetectorName, collectionName[0]};
    const auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
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
    const auto position{muc::midpoint(preStepPoint.GetPosition(), postStepPoint.GetPosition())};
    // retrive wire position
    const auto cellID{touchable.GetReplicaNumber(1)};
    const auto& cellInfo{fCellMap->at(cellID)};
    assert(cellID == cellInfo.cellID);
    const auto xWire{VectorCast<G4TwoVector>(cellInfo.position)};
    const auto tWire{VectorCast<G4ThreeVector>(cellInfo.direction)};
    // calculate drift distance
    const auto commonNormal{tWire.cross(muc::midpoint(preStepPoint.GetMomentum(), postStepPoint.GetMomentum()))};
    const auto driftDistance{std::abs((position - xWire).dot(commonNormal)) / commonNormal.mag()};
    const auto driftTime{driftDistance / fMeanDriftVelocity};
    const auto hitTime{muc::midpoint(preStepPoint.GetGlobalTime(), postStepPoint.GetGlobalTime())};
    const auto signalTime{hitTime + driftTime};
    // vertex Ek and p
    const auto vertexEk{track.GetVertexKineticEnergy()};
    const auto vertexMomentum{track.GetVertexMomentumDirection() * std::sqrt(vertexEk * (vertexEk + 2 * particle.GetPDGMass()))};
    // track creator process
    const auto creatorProcess{track.GetCreatorProcess()};
    // new a hit
    const auto& hit{fSplitHit[cellID].emplace_back(std::make_unique_for_overwrite<CDCHit>())};
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

    return true;
}

auto CDCSD::EndOfEvent(G4HCofThisEvent*) -> void {
    fHitsCollection->GetVector()->reserve(
        muc::ranges::accumulate(fSplitHit, 0,
                                 [](auto&& count, auto&& cellHit) {
                                     return count + cellHit.second.size();
                                 }));

    constexpr auto ByTrackID{
        [](const auto& hit1, const auto& hit2) {
            return Get<"TrkID">(*hit1) < Get<"TrkID">(*hit2);
        }};
    for (int hitID{};
         auto&& [cellID, splitHit] : fSplitHit) {
        switch (splitHit.size()) {
        case 0:
            std23::unreachable();
        case 1: {
            auto& hit{splitHit.front()};
            Get<"HitID">(*hit) = hitID++;
            assert(Get<"CellID">(*hit) == cellID);
            fHitsCollection->insert(hit.release());
        } break;
        default: {
            const auto timeResolutionFWHM{Detector::Description::CDC::Instance().TimeResolutionFWHM()};
            assert(timeResolutionFWHM >= 0);
            // sort hit by signal time
            gfx::timsort(splitHit,
                         [](const auto& hit1, const auto& hit2) {
                             return Get<"t">(*hit1) < Get<"t">(*hit2);
                         });
            // loop over all hits on this cell and cluster to real hits by signal times
            std::ranges::subrange cluster{splitHit.begin(), splitHit.begin()};
            while (cluster.end() != splitHit.end()) {
                const auto tFirst{*Get<"t">(**cluster.end())};
                const auto windowClosingTime{tFirst + timeResolutionFWHM};
                if (tFirst == windowClosingTime and // Notice: bad numeric with huge Get<"t">(**clusterFirst)!
                    timeResolutionFWHM != 0) [[unlikely]] {
                    Env::PrintLnWarning("Warning: A huge time ({}) completely rounds off the time resolution ({})", tFirst, timeResolutionFWHM);
                }
                cluster = {cluster.end(), std::ranges::find_if_not(cluster.end(), splitHit.end(),
                                                                   [&windowClosingTime](const auto& hit) {
                                                                       return Get<"t">(*hit) <= windowClosingTime;
                                                                   })};
                // find top hit
                auto& topHit{*std::ranges::min_element(cluster, ByTrackID)};
                // construct real hit
                Get<"HitID">(*topHit) = hitID++;
                assert(Get<"CellID">(*topHit) == cellID);
                int nTopHit{};
                for (const auto& hit : cluster) {
                    if (hit == topHit) { continue; }
                    Get<"Edep">(*topHit) += Get<"Edep">(*hit); // sum
                    if (Get<"TrkID">(*hit) == Get<"TrkID">(*topHit)) {
                        ++nTopHit;
                        Get<"tHit">(*topHit) += Get<"tHit">(*hit); // mean
                        *Get<"x">(*topHit) += *Get<"x">(*hit);     // mean
                    }
                }
                Get<"tHit">(*topHit) /= nTopHit; // mean
                *Get<"x">(*topHit) /= nTopHit;   // mean
                fHitsCollection->insert(topHit.release());
            }
        } break;
        }
    }
    fSplitHit.clear();

    gfx::timsort(*fHitsCollection->GetVector(), ByTrackID);
}

} // namespace MACE::inline Simulation::inline SD
