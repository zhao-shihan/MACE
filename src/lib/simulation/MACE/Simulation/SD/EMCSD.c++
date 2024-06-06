#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Env/Print.h++"
#include "MACE/External/gfx/timsort.hpp"
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

#include "muc/numeric"

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
    muc::ranges::adjacent_difference(emc.CsIEnergyBin(), dE.begin());
    std::vector<double> spectrum(emc.CsIScintillationComponent1().size());
    muc::ranges::adjacent_difference(emc.CsIEnergyBin(), spectrum.begin(), muc::midpoint<double>);
    const auto integral{std::inner_product(next(spectrum.cbegin()), spectrum.cend(), next(dE.cbegin()), 0.)};
    std::vector<double> meanE(emc.CsIEnergyBin().size());
    muc::ranges::adjacent_difference(emc.CsIEnergyBin(), meanE.begin(), muc::midpoint<double>);
    std::ranges::transform(spectrum, meanE, spectrum.begin(), std::multiplies{});
    fEnergyDepositionThreshold = std::inner_product(next(spectrum.cbegin()), spectrum.cend(), next(dE.cbegin()), 0.) / integral;

    fSplitHit.reserve(emc.NUnit());
}

auto EMCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHitsCollection = new EMCHitCollection{SensitiveDetectorName, collectionName[0]};
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
            assert(scintillationTimeConstant1 >= 0);
            // sort hit by time
            gfx::timsort(splitHit,
                         [](const auto& hit1, const auto& hit2) {
                             return Get<"t">(*hit1) < Get<"t">(*hit2);
                         });
            // loop over all hits on this crystal and cluster to real hits by times
            std::ranges::subrange cluster{splitHit.begin(), splitHit.begin()};
            while (cluster.end() != splitHit.end()) {
                const auto tFirst{*Get<"t">(**cluster.end())};
                const auto windowClosingTime{tFirst + scintillationTimeConstant1};
                if (tFirst == windowClosingTime and // Notice: bad numeric with huge Get<"t">(**clusterFirst)!
                    scintillationTimeConstant1 != 0) [[unlikely]] {
                    Env::PrintLnWarning("Warning: A huge time ({}) completely rounds off the time resolution ({})", tFirst, scintillationTimeConstant1);
                }
                cluster = {cluster.end(), std::ranges::find_if_not(cluster.end(), splitHit.end(),
                                                                   [&windowClosingTime](const auto& hit) {
                                                                       return Get<"t">(*hit) <= windowClosingTime;
                                                                   })};
                // find top hit
                auto& topHit{*std::ranges::min_element(cluster, ByTrackID)};
                // construct real hit
                Get<"HitID">(*topHit) = hitID++;
                assert(Get<"UnitID">(*topHit) == unitID);
                for (const auto& hit : cluster) {
                    if (hit == topHit) { continue; }
                    Get<"Edep">(*topHit) += Get<"Edep">(*hit);
                }
                fHitsCollection->insert(topHit.release());
            }
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
