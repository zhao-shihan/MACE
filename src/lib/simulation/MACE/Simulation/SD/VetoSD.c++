#include "MACE/Detector/Description/PDSVeto.h++"
#include "MACE/Simulation/SD/VetoPMSD.h++"
#include "MACE/Simulation/SD/VetoSD.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Utility/PrettyLog.h++"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4OpticalPhoton.hh"
#include "G4ParticleDefinition.hh"
#include "G4RotationMatrix.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VProcess.hh"
#include "G4VTouchable.hh"

#include "muc/algorithm"
#include "muc/numeric"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iterator>
#include <numeric>
#include <ranges>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

namespace MACE::inline Simulation::inline SD {
using namespace MACE::Detector::Description;

VetoSD::VetoSD(const G4String& sdName, const VetoPMSD* vetoPMSD) :
    // Mustard::NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fVetoPMSD{vetoPMSD},
    fEnergyDepositionThreshold{},
    fSplitHit{},
    fHitsCollection{} {
    vetoPMSD->NOpticalPhotonHit();
    collectionName.insert(sdName + "HC");

    const auto& veto{Detector::Description::PDSVeto::Instance()};
    assert(veto.PSScintillationEnergyBin().size() == veto.PSScintillationComponent1().size());
    std::vector<double> dE(veto.PSScintillationEnergyBin().size());
    muc::ranges::adjacent_difference(veto.PSScintillationEnergyBin(), dE.begin());
    std::vector<double> spectrum(veto.PSScintillationComponent1().size());
    muc::ranges::adjacent_difference(veto.PSScintillationEnergyBin(), spectrum.begin(), muc::midpoint<double>);
    const auto integral{std::inner_product(next(spectrum.cbegin()), spectrum.cend(), next(dE.cbegin()), 0.)};
    std::vector<double> meanE(veto.PSScintillationEnergyBin().size());
    muc::ranges::adjacent_difference(veto.PSScintillationEnergyBin(), meanE.begin(), muc::midpoint<double>);
    std::ranges::transform(spectrum, meanE, spectrum.begin(), std::multiplies{});
    fEnergyDepositionThreshold = std::inner_product(next(spectrum.cbegin()), spectrum.cend(), next(dE.cbegin()), 0.) / integral;

    fSplitHit.reserve(veto.NStrip());
}

auto VetoSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHitsCollection = new VetoHitCollection{SensitiveDetectorName, collectionName[0]};
    const auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto VetoSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step{*theStep};
    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};

    if (&particle == G4OpticalPhoton::Definition()) { return false; }

    const auto eDep{step.GetTotalEnergyDeposit()};

    if (eDep < fEnergyDepositionThreshold) { return false; }
    assert(eDep > 0);

    const auto& preStepPoint{*step.GetPreStepPoint()};
    const auto& touchable{*preStepPoint.GetTouchable()};

    // replica number list 0_strip, 1_stripBox, 2_moduleBox
    const auto moduleID{touchable.GetReplicaNumber(2)};
    const auto stripID{[&]() {
        const auto& veto{PDSVeto::Instance()};
        const auto stripLocalID{touchable.GetReplicaNumber(1)};
        return stripLocalID + veto.StartingStripIDOfAModule()[moduleID];
    }()};

    // calculate (Ek0, p0)
    const auto vertexEk{track.GetVertexKineticEnergy()};
    const auto vertexMomentum{track.GetVertexMomentumDirection() * std::sqrt(vertexEk * (vertexEk + 2 * particle.GetPDGMass()))};
    // track creator process
    const auto creatorProcess{track.GetCreatorProcess()};
    // new a hit
    const auto& hit{fSplitHit[stripID].emplace_back(std::make_unique_for_overwrite<VetoHit>())};
    Get<"EvtID">(*hit) = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    Get<"HitID">(*hit) = -1; // to be determined
    Get<"StripID">(*hit) = stripID;
    Get<"ModuleID">(*hit) = moduleID;
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

auto VetoSD::EndOfEvent(G4HCofThisEvent*) -> void {
    const auto& veto{PDSVeto::Instance()};
    fHitsCollection->GetVector()->reserve(
        muc::ranges::accumulate(fSplitHit, 0,
                                [](auto&& count, auto&& cellHit) {
                                    return count + cellHit.second.size();
                                }));

    for (auto&& [stripID, splitHit] : fSplitHit) {
        switch (splitHit.size()) {
        case 0:
            muc::unreachable();
        case 1: {
            auto& hit{splitHit.front()};
            assert(Get<"StripID">(*hit) == stripID);
            fHitsCollection->insert(hit.release());
        } break;
        default: {
            const auto scintillationTimeConstant1{Detector::Description::PDSVeto::Instance().PSScintillationTimeConstant1()};
            assert(scintillationTimeConstant1 >= 0);
            // sort hit by time
            muc::timsort(splitHit,
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
                    Mustard::PrettyWarning(fmt::format("A huge time ({}) completely rounds off the time resolution ({})", tFirst, scintillationTimeConstant1));
                }
                cluster = {cluster.end(), std::ranges::find_if_not(cluster.end(), splitHit.end(),
                                                                   [&windowClosingTime](const auto& hit) {
                                                                       return Get<"t">(*hit) <= windowClosingTime;
                                                                   })};
                // find top hit
                auto& topHit{*std::ranges::min_element(cluster,
                                                       [](const auto& hit1, const auto& hit2) {
                                                           return Get<"TrkID">(*hit1) < Get<"TrkID">(*hit2);
                                                       })};
                // construct real hit
                assert(Get<"StripID">(*topHit) == stripID);
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

    muc::timsort(*fHitsCollection->GetVector(),
                 [](const auto& hit1, const auto& hit2) {
                     return std::tie(Get<"TrkID">(*hit1), Get<"t">(*hit1)) <
                            std::tie(Get<"TrkID">(*hit2), Get<"t">(*hit2));
                 });

    for (int hitID{}; auto&& hit : *fHitsCollection->GetVector()) {
        Get<"HitID">(*hit) = hitID++;
    }

    if (fVetoPMSD) {
        auto nHit{fVetoPMSD->NOpticalPhotonHit()};
        auto nHitOnEachSiPM{fVetoPMSD->NOpticalPhotonOnEachSiPM()};
        for (auto&& hit : std::as_const(*fHitsCollection->GetVector())) {
            if (not nHit.empty()) {
                Get<"nOptPho">(*hit) = nHit.at(Get<"StripID">(*hit));
                Get<"nOptPhoOnEachSiPM">(*hit) = nHitOnEachSiPM.at(Get<"StripID">(*hit));
            } else {
                Get<"nOptPho">(*hit) = 0;
                Get<"nOptPhoOnEachSiPM">(*hit) = std::vector<int>(veto.FiberNum() * 2, 0);
            }
        }
    }
}

} // namespace MACE::inline Simulation::inline SD
