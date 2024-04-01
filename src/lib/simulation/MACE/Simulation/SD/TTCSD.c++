#include "MACE/Compatibility/std23/unreachable.h++"
#include "MACE/Detector/Description/TTC.h++"
#include "MACE/Env/Print.h++"
#include "MACE/Extension/stdx/ranges_numeric.h++"
#include "MACE/External/gfx/timsort.hpp"
#include "MACE/Math/MidPoint.h++"
#include "MACE/Simulation/SD/TTCSD.h++"
#include "MACE/Simulation/SD/TTCSiPMSD.h++"

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

TTCSD::TTCSD(const G4String& sdName, const TTCSiPMSD* ttcSiPMSD) :
    NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fTTCSiPMSD{ttcSiPMSD},
    fEnergyDepositionThreshold{},
    fSplitHit{},
    fHitsCollection{} {
    collectionName.insert(sdName + "HC");

    const auto& ttc{Detector::Description::TTC::Instance()};
    assert(ttc.ScintillationComponent1EnergyBin().size() == ttc.ScintillationComponent1().size());
    std::vector<double> dE(ttc.ScintillationComponent1EnergyBin().size());
    stdx::ranges::adjacent_difference(ttc.ScintillationComponent1EnergyBin(), dE.begin());
    std::vector<double> spectrum(ttc.ScintillationComponent1().size());
    stdx::ranges::adjacent_difference(ttc.ScintillationComponent1EnergyBin(), spectrum.begin(), Math::MidPoint<double, double>);
    const auto integral{std::inner_product(next(spectrum.cbegin()), spectrum.cend(), next(dE.cbegin()), 0.)};
    std::vector<double> meanE(ttc.ScintillationComponent1EnergyBin().size());
    stdx::ranges::adjacent_difference(ttc.ScintillationComponent1EnergyBin(), meanE.begin(), Math::MidPoint<double, double>);
    std::ranges::transform(spectrum, meanE, spectrum.begin(), std::multiplies{});
    fEnergyDepositionThreshold = std::inner_product(next(spectrum.cbegin()), spectrum.cend(), next(dE.cbegin()), 0.) / integral;

    fSplitHit.reserve(ttc.NAlongPhi() * ttc.NAlongZ());
}

auto TTCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHitsCollection = new TTCHitCollection(SensitiveDetectorName, collectionName[0]);
    const auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto TTCSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step{*theStep};
    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};

    if (&particle == G4OpticalPhoton::Definition()) { return false; }

    const auto eDep{step.GetTotalEnergyDeposit()};

    if (eDep < fEnergyDepositionThreshold) { return false; }
    assert(eDep > 0);

    const auto& preStepPoint{*step.GetPreStepPoint()};
    const auto tileID{preStepPoint.GetTouchable()->GetReplicaNumber()};
    // calculate (Ek0, p0)
    const auto vertexEk{track.GetVertexKineticEnergy()};
    const auto vertexMomentum{track.GetVertexMomentumDirection() * std::sqrt(vertexEk * (vertexEk + 2 * particle.GetPDGMass()))};
    // track creator process
    const auto creatorProcess{track.GetCreatorProcess()};
    // new a hit
    const auto& hit{fSplitHit[tileID].emplace_back(std::make_unique_for_overwrite<TTCHit>())};
    Get<"EvtID">(*hit) = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    Get<"HitID">(*hit) = -1; // to be determined
    Get<"TileID">(*hit) = tileID;
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

    return true;
}

auto TTCSD::EndOfEvent(G4HCofThisEvent*) -> void {
    constexpr auto ByTrackID{
        [](const auto& hit1, const auto& hit2) {
            return Get<"TrkID">(*hit1) < Get<"TrkID">(*hit2);
        }};
    for (int hitID{};
         auto&& [tileID, splitHit] : fSplitHit) {
        switch (splitHit.size()) {
        case 0:
            std23::unreachable();
        case 1: {
            auto& hit{splitHit.front()};
            Get<"HitID">(*hit) = hitID++;
            assert(Get<"TileID">(*hit) == tileID);
            fHitsCollection->insert(hit.release());
        } break;
        default: {
            const auto scintillationTimeConstant1{Detector::Description::TTC::Instance().ScintillationTimeConstant1()};
            assert(scintillationTimeConstant1 >= 0);
            // sort hit by time
            gfx::timsort(splitHit,
                         [](const auto& hit1, const auto& hit2) {
                             return Get<"t">(*hit1) < Get<"t">(*hit2);
                         });
            // loop over all hits on this tile and cluster to real hits by times
            auto clusterFirst{splitHit.begin()};
            auto clusterLast{clusterFirst};
            do {
                const auto tFirst{*Get<"t">(**clusterFirst)};
                const auto windowClosingTime{tFirst + scintillationTimeConstant1};
                if (tFirst == windowClosingTime and // Notice: bad numeric with huge Get<"t">(**clusterFirst)!
                    scintillationTimeConstant1 != 0) [[unlikely]] {
                    Env::PrintLnWarning("CDCSD Warning: A huge time ({}) completely rounds off the time resolution ({})", tFirst, scintillationTimeConstant1);
                }
                clusterLast = std::ranges::find_if_not(clusterFirst, splitHit.end(),
                                                       [&windowClosingTime](const auto& hit) {
                                                           return Get<"t">(*hit) <= windowClosingTime;
                                                       });
                // find top hit
                auto& topHit{*std::ranges::min_element(clusterFirst, clusterLast, ByTrackID)};
                // construct real hit
                Get<"HitID">(*topHit) = hitID++;
                assert(Get<"TileID">(*topHit) == tileID);
                for (const auto& hit : std::ranges::subrange{clusterFirst, clusterLast}) {
                    if (hit == topHit) { continue; }
                    Get<"Edep">(*topHit) += Get<"Edep">(*hit);
                }
                fHitsCollection->insert(topHit.release());
                clusterFirst = clusterLast;
            } while (clusterFirst != splitHit.end());
        } break;
        }
    }
    fSplitHit.clear();
    gfx::timsort(*fHitsCollection->GetVector(), ByTrackID);

    if (fTTCSiPMSD) {
        auto nHit{fTTCSiPMSD->NOpticalPhotonHit()};
        for (auto&& hit : std::as_const(*fHitsCollection->GetVector())) {
            Get<"nOptPho">(*hit) = nHit[Get<"TileID">(*hit)];
        }
    }
}

} // namespace MACE::inline Simulation::inline SD
