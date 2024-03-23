#include "MACE/Detector/Description/STC.h++"
#include "MACE/Extension/stdx/ranges_numeric.h++"
#include "MACE/External/gfx/timsort.hpp"
#include "MACE/Math/MidPoint.h++"
#include "MACE/Simulation/SD/STCSD.h++"
#include "MACE/Simulation/SD/STCSiPMSD.h++"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4OpticalPhoton.hh"
#include "G4ParticleDefinition.hh"
#include "G4RotationMatrix.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VProcess.hh"
#include "G4VTouchable.hh"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iterator>
#include <numeric>
#include <string_view>
#include <utility>
#include <vector>

namespace MACE::inline Simulation::inline SD {

STCSD::STCSD(const G4String& sdName, const STCSiPMSD* stcSiPMSD) :
    NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fSTCSiPMSD{stcSiPMSD},
    fEnergyDepositionThreshold{},
    fSplitHit{},
    fHitsCollection{} {
    collectionName.insert(sdName + "HC");
    const auto& stc{Detector::Description::STC::Instance()};
    assert(stc.ScintillationComponent1EnergyBin().size() == stc.ScintillationComponent1().size());
    std::vector<double> dE(stc.ScintillationComponent1EnergyBin().size());
    stdx::ranges::adjacent_difference(stc.ScintillationComponent1EnergyBin(), dE.begin());
    std::vector<double> spectrum(stc.ScintillationComponent1().size());
    stdx::ranges::adjacent_difference(stc.ScintillationComponent1EnergyBin(), spectrum.begin(), Math::MidPoint<double, double>);
    const auto integral{std::inner_product(next(spectrum.cbegin()), spectrum.cend(), next(dE.cbegin()), 0.)};
    std::vector<double> meanE(stc.ScintillationComponent1EnergyBin().size());
    stdx::ranges::adjacent_difference(stc.ScintillationComponent1EnergyBin(), meanE.begin(), Math::MidPoint<double, double>);
    std::ranges::transform(spectrum, meanE, spectrum.begin(), std::multiplies{});
    fEnergyDepositionThreshold = std::inner_product(next(spectrum.cbegin()), spectrum.cend(), next(dE.cbegin()), 0.) / integral;
}

auto STCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHitsCollection = new STCHitCollection(SensitiveDetectorName, collectionName[0]);
    const auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto STCSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step{*theStep};
    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};

    if (&particle == G4OpticalPhoton::Definition()) { return false; }

    const auto eDep{step.GetTotalEnergyDeposit()};

    if (eDep < fEnergyDepositionThreshold) { return false; }
    assert(eDep > 0);

    const auto& preStepPoint{*step.GetPreStepPoint()};
    const auto detectorID{preStepPoint.GetTouchable()->GetReplicaNumber()};
    // calculate (Ek0, p0)
    const auto vertexEk{track.GetVertexKineticEnergy()};
    const auto vertexMomentum{track.GetVertexMomentumDirection() * std::sqrt(vertexEk * (vertexEk + 2 * particle.GetPDGMass()))};
    // track creator process
    const auto creatorProcess{track.GetCreatorProcess()};
    // new a hit
    auto hit{std::make_unique_for_overwrite<STCHit>()};
    Get<"EvtID">(*hit) = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    Get<"HitID">(*hit) = -1; // to be determined
    Get<"DetID">(*hit) = detectorID;
    Get<"t">(*hit) = preStepPoint.GetGlobalTime();
    Get<"Edep">(*hit) = eDep;
    Get<"nOptPho">(*hit) = -1; // to be determined
    Get<"x">(*hit) = preStepPoint.GetPosition();
    Get<"Ek">(*hit) = preStepPoint.GetKineticEnergy();
    Get<"p">(*hit) = preStepPoint.GetMomentum();
    Get<"TrkID">(*hit) = track.GetTrackID();
    Get<"PDGID">(*hit) = particle.GetPDGEncoding();
    Get<"t0">(*hit) = track.GetGlobalTime() - track.GetLocalTime();
    Get<"x0">(*hit) = track.GetVertexPosition();
    Get<"Ek0">(*hit) = vertexEk;
    Get<"p0">(*hit) = vertexMomentum;
    *Get<"CreatProc">(*hit) = creatorProcess ? std::string_view{creatorProcess->GetProcessName()} : "|0>";
    fSplitHit[detectorID].emplace_back(std::move(hit));

    return true;
}

auto STCSD::EndOfEvent(G4HCofThisEvent*) -> void {
    for (int hitID{};
         auto&& [detectorID, splitHit] : fSplitHit) {
        switch (splitHit.size()) {
        case 0:
            break;
        case 1: {
            auto& hit{splitHit.front()};
            Get<"HitID">(*hit) = hitID++;
            assert(Get<"DetID">(*hit) == detectorID);
            fHitsCollection->insert(hit.release());
        } break;
        default: {
            const auto scintillationTimeConstant1{Detector::Description::STC::Instance().ScintillationTimeConstant1()};
            // sort hit by time
            gfx::timsort(splitHit,
                         [](const auto& hit1, const auto& hit2) {
                             return Get<"t">(*hit1) < Get<"t">(*hit2);
                         });
            // loop over all hits on this crystal and cluster to real hits by times
            std::vector<std::unique_ptr<STCHit>*> hitCandidate;
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
                    assert(Get<"DetID">(**topHit) == detectorID);
                    for (auto&& hit : std::as_const(hitCandidate)) {
                        if (hit == topHit) { continue; }
                        Get<"Edep">(**topHit) += Get<"Edep">(**hit);
                    }
                    fHitsCollection->insert(topHit->release());
                }};
            for (auto windowClosingTime{Get<"t">(*splitHit.front()) + scintillationTimeConstant1};
                 auto&& aSplitHit : splitHit) {
                if (Get<"t">(*aSplitHit) > windowClosingTime) {
                    ClusterAndInsertHit();
                    hitCandidate.clear();
                    windowClosingTime = Get<"t">(*aSplitHit) + scintillationTimeConstant1;
                }
                hitCandidate.emplace_back(&aSplitHit);
            }
            ClusterAndInsertHit();
        } break;
        }
        splitHit.clear();
    }
    if (fSTCSiPMSD != nullptr) {
        auto nHit{fSTCSiPMSD->NOpticalPhotonHit()};
        for (auto&& hit : std::as_const(*fHitsCollection->GetVector())) {
            Get<"nOptPho">(*hit) = nHit[Get<"DetID">(*hit)];
        }
    }
}

} // namespace MACE::inline Simulation::inline SD
