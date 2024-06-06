#pragma once

#include "MACE/Data/Tuple.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Math/Hypot.h++"
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Math/Norm.h++"
#include "MACE/Utility/PhysicalConstant.h++"
#include "MACE/Utility/VectorArithmeticOperator.h++"

#include "muc/array"

#include <cmath>
#include <vector>

namespace MACE::Data {

using MMSTrack = TupleModel<Value<int, "EvtID", "Event ID">,
                            Value<int, "TrkID", "Track ID">,
                            Value<std::vector<int>, "HitID", "Hit(ID)s in this track">,
                            Value<float, "chi2", "Goodness of fit (chi^{2})">,
                            Value<double, "t0", "Vertex time">,
                            // vertex information
                            Value<int, "PDGID", "Particle PDG ID">,
                            Value<muc::array3f, "x0", "Vertex position">,
                            Value<float, "Ek0", "Vertex kinetic energy">,
                            Value<muc::array3f, "p0", "Vertex momentum">,
                            // helix information
                            Value<muc::array2f, "c0", "Transverse center">,
                            Value<float, "r0", "Transverse radius">,
                            Value<float, "phi0", "Vertex azimuth angle">,
                            Value<float, "z0", "Vertex z coordinate">,
                            Value<float, "theta0", "Reference zenith angle">>;

using MMSSimTrack = TupleModel<MMSTrack,
                               Value<std::string, "CreatProc", "Track creator process (MC truth)">>;

/// @brief Calculate helix information from known vertex information in-place.
/// @param track The track
/// @param magneticFluxDensity Magnetic field B0
constexpr auto CalculateHelix(SuperTuple<Data::Tuple<MMSTrack>> auto& track, double magneticFluxDensity) -> void {
    using PhysicalConstant::c_light;

    const auto charge{Get<"PDGID">(track) > 0 ? -1 : 1};
    const auto x0{Get<"x0">(track).template As<muc::array3d>()};
    const auto p0{Get<"p0">(track).template As<muc::array3d>()};

    const auto absPXY{Math::Hypot(p0[0], p0[1])};
    const auto pXY{charge < 0 ? absPXY : -absPXY};
    const auto r0{pXY / (-charge * magneticFluxDensity * c_light)};
    const muc::array2d x0Local{r0 * (p0[1] / pXY),
                                r0 * (-p0[0] / pXY)};
    const auto phi0{std::atan2(-x0Local[1], -x0Local[0])};
    const muc::array2d c0{x0[0] - x0Local[0],
                           x0[1] - x0Local[1]};

    // const auto absDeltaPhi{std::acos(-c0 * x0Local) / std::sqrt(Math::Norm2(c0) * Math::Norm2(x0Local))};
    // const auto deltaPhi{x0Local[0] * c0[1] - c0[0] * x0Local[1] > 0 ? absDeltaPhi : -absDeltaPhi};
    const auto theta0{std::atan2(pXY, p0[2])};
    // const auto z0{x0[3] - r0 * deltaPhi / std::tan(theta0)};
    const auto z0{x0[2]};

    Get<"c0">(track) = c0;
    Get<"r0">(track) = r0;
    Get<"phi0">(track) = phi0;
    Get<"z0">(track) = z0;
    Get<"theta0">(track) = theta0;
}

/// @brief Calculate vertex information from known helix information in-place.
/// @param track The track
/// @param magneticFluxDensity Magnetic field B0
constexpr auto CalculateVertex(SuperTuple<Data::Tuple<MMSTrack>> auto& track, double magneticFluxDensity) -> void {
    using PhysicalConstant::c_light;
    using PhysicalConstant::electron_mass_c2;

    const auto c0{Get<"c0">(track)};
    const auto r0{Get<"r0">(track)};
    const auto phi0{Get<"phi0">(track)};
    const auto z0{Get<"z0">(track)};
    const auto theta0{Get<"theta0">(track)};

    const auto charge{theta0 > 0 ? -1 : 1};
    const auto pdgID{charge < 0 ? 11 : -11};

    const auto cos0{std::cos(phi0)};
    const auto sin0{std::sin(phi0)};
    const muc::array3d x0{c0[0] + r0 * cos0,
                           c0[1] + r0 * sin0,
                           z0};

    const auto pXY{-charge * magneticFluxDensity * c_light * r0};
    const auto pZ{pXY / std::tan(theta0)};
    const auto ek0{std::sqrt(Math::Hypot2(pXY, pZ) + Math::Pow<2>(electron_mass_c2)) - electron_mass_c2};
    const muc::array3d p0{-pXY * sin0,
                           pXY * cos0,
                           pZ};

    Get<"PDGID">(track) = pdgID;
    Get<"x0">(track) = x0;
    Get<"Ek0">(track) = ek0;
    Get<"p0">(track) = p0;
}

} // namespace MACE::Data
