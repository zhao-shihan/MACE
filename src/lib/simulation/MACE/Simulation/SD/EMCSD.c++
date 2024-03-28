#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Extension/stdx/ranges_numeric.h++"
#include "MACE/External/gfx/timsort.hpp"
#include "MACE/Math/MidPoint.h++"
#include "MACE/Simulation/SD/EMCPMTSD.h++"
#include "MACE/Simulation/SD/EMCSD.h++"

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
#include <ranges>
#include <string_view>
#include <utility>
#include <vector>

namespace MACE::inline Simulation::inline SD {

EMCSD::EMCSD(const G4String& sdName, const EMCPMTSD* emcPMTSD) :
    NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fEMCPMTSD{emcPMTSD},
    fEnergyDepositionThreshold{},
    fSplitHit{},
    fHitsCollection{} {
    collectionName.insert(sdName + "HC");

    const auto& emc{Detector::Description::EMC::Instance()};
    assert(emc.CsIEnergyBin().size() == emc.CsIScintillationComponent1().size());
    std::vector<double> dE(emc.CsIEnergyBin().size());
    stdx::ranges::adjacent_difference(emc.CsIEnergyBin(), dE.begin());
    std::vector<double> spectrum(emc.CsIScintillationComponent1().size());
    stdx::ranges::adjacent_difference(emc.CsIEnergyBin(), spectrum.begin(), Math::MidPoint<double, double>);
    const auto integral{std::inner_product(next(spectrum.cbegin()), spectrum.cend(), next(dE.cbegin()), 0.)};
    std::vector<double> meanE(emc.CsIEnergyBin().size());
    stdx::ranges::adjacent_difference(emc.CsIEnergyBin(), meanE.begin(), Math::MidPoint<double, double>);
    std::ranges::transform(spectrum, meanE, spectrum.begin(), std::multiplies{});
    fEnergyDepositionThreshold = std::inner_product(next(spectrum.cbegin()), spectrum.cend(), next(dE.cbegin()), 0.) / integral;

    fSplitHit.reserve(emc.NUnit());
}

auto EMCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHitsCollection = new EMCHitCollection(SensitiveDetectorName, collectionName[0]);
    const auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto EMCSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step{*theStep};
    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};

    if (&particle == G4OpticalPhoton::Definition()) { return false; }

    const auto eDep{step.GetTotalEnergyDeposit()};

    if (eDep < fEnergyDepositionThreshold) { return false; }
    assert(eDep > 0);

    const auto& preStepPoint{*step.GetPreStepPoint()};
    const auto& touchable{*preStepPoint.GetTouchable()};
    const auto unitID{touchable.GetReplicaNumber()};
    // calculate (Ek0, p0)
    const auto vertexEk{track.GetVertexKineticEnergy()};
    const auto vertexMomentum{track.GetVertexMomentumDirection() * std::sqrt(vertexEk * (vertexEk + 2 * particle.GetPDGMass()))};
    // track creator process
    const auto creatorProcess{track.GetCreatorProcess()};
    // new a hit
    const auto& hit{fSplitHit[unitID].emplace_back(std::make_unique_for_overwrite<EMCHit>())};
    Get<"EvtID">(*hit) = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    Get<"HitID">(*hit) = -1; // to be determined
    Get<"UnitID">(*hit) = unitID;
    Get<"t">(*hit) = preStepPoint.GetGlobalTime();
    Get<"Edep">(*hit) = eDep;
    Get<"nOptPho">(*hit) = -1; // to be determined
    Get<"x">(*hit) = preStepPoint.GetPosition() - touchable.GetTranslation();
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

auto EMCSD::EndOfEvent(G4HCofThisEvent*) -> void {
    constexpr auto ByTrackID{
        [](const auto& hit1, const auto& hit2) {
            return Get<"TrkID">(*hit1) < Get<"TrkID">(*hit2);
        }};
    for (int hitID{};
         auto&& [unitID, splitHit] : fSplitHit) {
        switch (splitHit.size()) {
        case 0:
            std23::unreachable();
        case 1: {
            auto& hit{splitHit.front()};
            Get<"HitID">(*hit) = hitID++;
            assert(Get<"UnitID">(*hit) == unitID);
            fHitsCollection->insert(hit.release());
        } break;
        default: {
            const auto scintillationTimeConstant1{Detector::Description::EMC::Instance().ScintillationTimeConstant1()};
            // sort hit by time
            gfx::timsort(splitHit,
                         [](const auto& hit1, const auto& hit2) {
                             return Get<"t">(*hit1) < Get<"t">(*hit2);
                         });
            // loop over all hits on this crystal and cluster to real hits by times
            double windowClosingTime;
            auto clusterFirst{splitHit.begin()};
            auto clusterLast{clusterFirst};
            do {
                windowClosingTime = Get<"t">(**clusterFirst) + scintillationTimeConstant1;
                clusterLast = std::ranges::find_if_not(clusterFirst, splitHit.end(),
                                                       [&windowClosingTime](const auto& hit) {
                                                           return Get<"t">(*hit) < windowClosingTime;
                                                       });
                // find top hit
                auto& topHit{*std::ranges::min_element(clusterFirst, clusterLast, ByTrackID)};
                // construct real hit
                Get<"HitID">(*topHit) = hitID++;
                assert(Get<"UnitID">(*topHit) == unitID);
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

    if (fEMCPMTSD) {
        auto nHit{fEMCPMTSD->NOpticalPhotonHit()};
        for (auto&& hit : std::as_const(*fHitsCollection->GetVector())) {
            Get<"nOptPho">(*hit) = nHit[Get<"UnitID">(*hit)];
        }
    }
}

} // namespace MACE::inline Simulation::inline SD
