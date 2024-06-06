#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/TTC.h++"
#include "MACE/Simulation/Analysis/MMSTruthTracker.h++"

#include "gfx/timsort.hpp"

#include <cassert>
#include <utility>

namespace MACE::inline Simulation::Analysis {

MMSTruthTracker::MMSTruthTracker() :
    fMinNTTCHitForQualifiedTrack{2},
    fTrackFinder{},
    fMessengerRegister{this} {
    const auto& cdc{Detector::Description::CDC::Instance()};
    fTrackFinder.NHitThreshold(cdc.NSenseLayerPerSuper() * cdc.NSuperLayer());
}

auto MMSTruthTracker::operator()(const std::vector<gsl::owner<CDCHit*>>& cdcHitHC,
                                 const std::vector<gsl::owner<TTCHit*>>& ttcHitHC) -> std::vector<std::shared_ptr<Data::Tuple<Data::MMSSimTrack>>> {
    if (ssize(cdcHitHC) < fTrackFinder.NHitThreshold() or
        ssize(ttcHitHC) < fMinNTTCHitForQualifiedTrack) { return {}; }

    constexpr auto ByTrackID{
        [](const auto& hit1, const auto& hit2) {
            return Get<"TrkID">(*hit1) < Get<"TrkID">(*hit2);
        }};

    assert(std::ranges::is_sorted(cdcHitHC, ByTrackID));
    assert(std::ranges::is_sorted(ttcHitHC, ByTrackID));

    // find CDC hits coincidence with TTC hits

    std::vector<CDCHit*> coincidenceCDCHitHC;
    coincidenceCDCHitHC.reserve(cdcHitHC.size());

    std::ranges::subrange trackTTCHit{ttcHitHC.cbegin(), ttcHitHC.cbegin()};
    const auto trackCDCHitFirst{std::ranges::lower_bound(cdcHitHC, ttcHitHC.front(), ByTrackID)};
    std::ranges::subrange trackCDCHit{trackCDCHitFirst, trackCDCHitFirst};

    std::unordered_set<short> tileHit;
    tileHit.reserve(fMinNTTCHitForQualifiedTrack);

    while (trackTTCHit.end() != ttcHitHC.cend() and
           trackCDCHit.end() != cdcHitHC.cend()) {
        trackTTCHit = {trackTTCHit.end(), std::ranges::upper_bound(trackTTCHit.end(), ttcHitHC.cend(), *trackTTCHit.end(), ByTrackID)};
        trackCDCHit = {trackCDCHit.end(), std::ranges::upper_bound(trackCDCHit.end(), cdcHitHC.cend(), trackTTCHit.front(), ByTrackID)};

        if (std::ranges::ssize(trackTTCHit) < fMinNTTCHitForQualifiedTrack or
            std::ranges::ssize(trackCDCHit) < fTrackFinder.NHitThreshold()) {
            continue;
        }

        tileHit.clear();
        for (auto&& hit : trackTTCHit) {
            tileHit.emplace(Get<"TileID">(*hit));
        }
        if (ssize(tileHit) >= fMinNTTCHitForQualifiedTrack) {
            coincidenceCDCHitHC.insert(coincidenceCDCHitHC.end(), trackCDCHit.begin(), trackCDCHit.end());
        }
    }

    if (coincidenceCDCHitHC.empty()) { return {}; }

    // build track truths from hit

    auto mmsTrackDataNoCoincidence{fTrackFinder(coincidenceCDCHitHC).good};

    std::vector<std::shared_ptr<Data::Tuple<Data::MMSSimTrack>>> mmsTrackData;
    mmsTrackData.reserve(mmsTrackDataNoCoincidence.size());
    for (auto&& [_, track] : mmsTrackDataNoCoincidence) {
        mmsTrackData.emplace_back(std::move(track.seed));
    }

    return mmsTrackData;
}

} // namespace MACE::inline Simulation::Analysis
