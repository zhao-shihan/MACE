#pragma once

#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/Hit.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Data/TupleModel.h++"

#include <concepts>
#include <memory>
#include <vector>

namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<typename T>
concept Finder =
    requires {
        typename T::HitModel;
        typename T::TrackModel;
        requires Data::TupleModelContain<T::HitModel, Data::CDCHit>;
        requires Data::TupleModelContain<T::TrackModel, Data::MMSTrack>;
    } and
    requires(T finder, const int nextTrackID, const std::vector<std::shared_ptr<Data::Tuple<T::HitModel>>> hitData) {
        { finder(hitData, nextTrackID) };
        { finder(hitData, nextTrackID).NGoodTrack() } -> std::integral;
        { finder(hitData, nextTrackID).seed } -> std::convertible_to<std::unordered_map<int, std::shared_ptr<Data::Tuple<T::HitModel>>>>;
        { finder(hitData, nextTrackID).goodies } -> std::convertible_to<std::unordered_map<int, std::vector<std::shared_ptr<Data::Tuple<T::HitModel>>>>>;
        { finder(hitData, nextTrackID).garbage } -> std::convertible_to<std::vector<std::shared_ptr<Data::Tuple<T::HitModel>>>>;
    };

template<typename T>
concept SimFinder =
    requires {
        requires Finder<T>;
        requires Data::TupleModelContain<T::HitModel, Data::CDCSimHit>;
        requires Data::TupleModelContain<T::TrackModel, Data::MMSSimTrack>;
    };

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder
