#pragma once

#include "MACE/Data/Hit.h++"
#include "MACE/Data/MMSTrack.h++"
#include "Mustard/Data/Tuple.h++"
#include "Mustard/Data/TupleModel.h++"

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
        requires Mustard::Data::SuperTupleModel<T::Hit, Data::CDCHit>;
        requires Mustard::Data::SuperTupleModel<T::TrackModel, Data::MMSTrack>;
    } and
    requires(T finder, const int nextTrackID, const int trackID, const std::vector<Mustard::Data::Tuple<T::Hit>*> hitData) {
        { finder(hitData, nextTrackID) };
        { finder(hitData, nextTrackID).good[trackID].hitData } -> std::same_as<std::vector<Mustard::Data::Tuple<T::Hit>*>>;
        { finder(hitData, nextTrackID).good[trackID].seed } -> std::same_as<std::shared_ptr<Mustard::Data::Tuple<ATrack>>>;
        { finder(hitData, nextTrackID).garbage } -> std::same_as<std::vector<Mustard::Data::Tuple<T::Hit>*>>;
    } and
    requires(T finder, const int nextTrackID, const int trackID, const std::vector<std::unique_ptr<Mustard::Data::Tuple<T::Hit>>> hitData) {
        { finder(hitData, nextTrackID) };
        { finder(hitData, nextTrackID).good[trackID].hitData } -> std::same_as<std::vector<std::unique_ptr<Mustard::Data::Tuple<T::Hit>>>>;
        { finder(hitData, nextTrackID).good[trackID].seed } -> std::same_as<std::shared_ptr<Mustard::Data::Tuple<ATrack>>>;
        { finder(hitData, nextTrackID).garbage } -> std::same_as<std::vector<std::unique_ptr<Mustard::Data::Tuple<T::Hit>>>>;
    } and
    requires(T finder, const int nextTrackID, const int trackID, const std::vector<std::shared_ptr<Mustard::Data::Tuple<T::Hit>>> hitData) {
        { finder(hitData, nextTrackID) };
        { finder(hitData, nextTrackID).good[trackID].hitData } -> std::same_as<std::vector<std::shared_ptr<Mustard::Data::Tuple<T::Hit>>>>;
        { finder(hitData, nextTrackID).good[trackID].seed } -> std::same_as<std::shared_ptr<Mustard::Data::Tuple<ATrack>>>;
        { finder(hitData, nextTrackID).garbage } -> std::same_as<std::vector<std::shared_ptr<Mustard::Data::Tuple<T::Hit>>>>;
    };

template<typename T>
concept SimFinder =
    requires {
        requires Finder<T>;
        requires Mustard::Data::SuperTupleModel<T::Hit, Data::CDCSimHit>;
        requires Mustard::Data::SuperTupleModel<T::Track, Data::MMSSimTrack>;
    };

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder
