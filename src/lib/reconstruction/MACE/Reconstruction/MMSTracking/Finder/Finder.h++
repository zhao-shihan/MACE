#pragma once

#include "MACE/Data/Hit.h++"
#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Data/TupleModel.h++"

#include <concepts>
#include <iterator>
#include <memory>
#include <vector>

namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<typename T>
concept Finder =
    requires {
        typename T::Hit;
        typename T::Track;
        requires std::indirectly_readable<T::Hit>;
        requires Data::TupleContain<std::iter_value_t<T::Hit>, Data::Tuple<Data::CDCHit>>;
        requires Data::TupleModelContain<T::TrackModel, Data::MMSTrack>;
    } and
    requires(T finder, const int nextTrackID, const std::vector<T::Hit> hitData) {
        { finder(hitData, nextTrackID) };
        { finder(hitData, nextTrackID).NGoodTrack() } -> std::integral;
        { finder(hitData, nextTrackID).seed } -> std::convertible_to<std::unordered_map<int, T::Hit>>;
        { finder(hitData, nextTrackID).goodies } -> std::convertible_to<std::unordered_map<int, std::vector<T::Hit>>>;
        { finder(hitData, nextTrackID).garbage } -> std::convertible_to<std::vector<T::Hit>>;
    };

template<typename T>
concept SimFinder =
    requires {
        requires Finder<T>;
        requires Data::TupleModelContain<T::HitModel, Data::CDCSimHit>;
        requires Data::TupleModelContain<T::TrackModel, Data::MMSSimTrack>;
    };

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder
