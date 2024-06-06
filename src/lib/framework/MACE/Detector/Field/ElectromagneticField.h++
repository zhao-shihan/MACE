#pragma once

#include "MACE/Concept/NumericVector.h++"

#include "muc/array"

#include <concepts>

namespace MACE::Detector::Field {

template<typename F>
concept ElectromagneticField =
    requires(const F f, muc::array3d x) {
        { f.BFieldAt(x) } -> std::same_as<muc::array3d>;
        { f.EFieldAt(x) } -> std::same_as<muc::array3d>;
        { f.BEFieldAt(x).B } -> std::same_as<muc::array3d&&>;
        { f.BEFieldAt(x).E } -> std::same_as<muc::array3d&&>;
        { f.template BFieldAt<muc::array3d>({}) } -> std::same_as<muc::array3d>;
        { f.template EFieldAt<muc::array3d>({}) } -> std::same_as<muc::array3d>;
        { f.template BEFieldAt<muc::array3d>({}).B } -> std::same_as<muc::array3d&&>;
        { f.template BEFieldAt<muc::array3d>({}).E } -> std::same_as<muc::array3d&&>;
    };

} // namespace MACE::Detector::Field
