#pragma once

#include "MACE/Data/Hit.h++"
#include "MACE/Data/MMSTrack.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Data/TupleModel.h++"

#include <concepts>
#include <iterator>
#include <memory>
#include <vector>

namespace MACE::inline Reconstruction::MMSTracking::inline Fitter {

template<typename T>
concept Fitter =
    requires {
        typename T::Hit;
        typename T::Track;
        requires Mustard::Data::SuperTupleModel<typename T::Hit, Data::CDCHit>;
        requires Mustard::Data::SuperTupleModel<typename T::Track, Data::MMSTrack>;
    } and
    requires(T fitter, const std::vector<Mustard::Data::Tuple<typename T::Hit>*> hitData, const Mustard::Data::Tuple<typename T::Track>* seed) {
        { fitter(hitData, seed) } -> std::same_as<std::shared_ptr<Mustard::Data::Tuple<typename T::Track>>>;
    } and
    requires(T fitter, const std::vector<std::unique_ptr<Mustard::Data::Tuple<typename T::Hit>>> hitData, const std::unique_ptr<Mustard::Data::Tuple<typename T::Track>> seed) {
        { fitter(hitData, seed) } -> std::same_as<std::shared_ptr<Mustard::Data::Tuple<typename T::Track>>>;
    } and
    requires(T fitter, const std::vector<std::shared_ptr<Mustard::Data::Tuple<typename T::Hit>>> hitData, const std::shared_ptr<Mustard::Data::Tuple<typename T::Track>> seed) {
        { fitter(hitData, seed) } -> std::same_as<std::shared_ptr<Mustard::Data::Tuple<typename T::Track>>>;
    };

template<typename T>
concept SimFitter =
    requires {
        requires Fitter<T>;
        requires Mustard::Data::SuperTupleModel<typename T::Hit, Data::CDCSimHit>;
        requires Mustard::Data::SuperTupleModel<typename T::Track, Data::MMSSimTrack>;
    };

} // namespace MACE::inline Reconstruction::MMSTracking::inline Fitter
