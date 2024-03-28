#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/TTC.h++"
#include "MACE/External/gfx/timsort.hpp"
#include "MACE/Simulation/Analysis/MMSTruthTracker.h++"

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

    [[maybe_unused]] constexpr auto ByTrackID{
        [](const auto& hit1, const auto& hit2) {
            return Get<"TrkID">(*hit1) < Get<"TrkID">(*hit2);
        }};
    assert(std::ranges::is_sorted(cdcHitHC, ByTrackID));
    assert(std::ranges::is_sorted(ttcHitHC, ByTrackID));

    // build track truths from hit

    auto mmsTrackDataNoCoincidence{fTrackFinder(cdcHitHC).good};

    // find CDC track truths coincidence with TTC hits

    std::vector<std::shared_ptr<Data::Tuple<Data::MMSSimTrack>>> mmsTrackData;
    mmsTrackData.reserve(mmsTrackDataNoCoincidence.size());

    // iterate over TTC hits
    auto iTTCHit{ttcHitHC.cbegin()};
    auto iTrack{mmsTrackDataNoCoincidence.begin()};
    do {
        const auto ttcTrackID{Get<"TrkID">(**iTTCHit)};
        iTrack = std::ranges::find_if(iTrack, mmsTrackDataNoCoincidence.end(),
                                      [&ttcTrackID](const auto& track) {
                                          return Get<"TrkID">(*track.second.seed) >= ttcTrackID;
                                      });
        if (iTrack == mmsTrackDataNoCoincidence.end()) { break; }
        const auto nextTTCHit{std::ranges::find_if_not(iTTCHit, ttcHitHC.cend(),
                                                       [&ttcTrackID](const auto& hit) {
                                                           return Get<"TrkID">(*hit) == ttcTrackID;
                                                       })};
        if (auto& track{iTrack->second.seed};
            Get<"TrkID">(*track) == ttcTrackID and
            std::ranges::distance(iTTCHit, nextTTCHit) >= fMinNTTCHitForQualifiedTrack) {
            mmsTrackData.emplace_back(std::move(track));
            ++iTrack;
            /* // following scheme is too strong and lacks flexibility, no better way for now
            std::set<int> tileID;
            for (auto&& ttcHit : std::ranges::subrange{iTTCHit, nextTTCHit}) {
                tileID.emplace(Get<"TileID">(*ttcHit));
            }
            // check TTC coincidence
            if (ssize(tileID) >= fMinNTTCHitForQualifiedTrack) {
                auto lastID{*std::ranges::prev(tileID.cend())};
                for (auto&& id : std::as_const(tileID)) {
                    // if coincidence, break the loop and insert track to result
                    if (std23::abs(id - lastID) < fMinNTTCHitForQualifiedTrack) {
                        mmsTrackData.emplace_back(std::move(track));
                        break;
                    }
                }
            } */
        }
        iTTCHit = nextTTCHit;
    } while (iTTCHit != ttcHitHC.cend());

    return mmsTrackData;
}

} // namespace MACE::inline Simulation::Analysis
