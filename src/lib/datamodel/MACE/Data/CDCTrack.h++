#pragma once

#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Extension/stdx/arraynx.h++"

namespace MACE::Data {

using CDCTrack = TupleModel<Value<int, "evtID", "Event ID">,
                            Value<int, "trkID", "Track ID">,
                            Value<int, "pdgID", "Particle PDG ID">,
                            Value<int, "nHit", "Number of hits fitted">,
                            Value<float, "chi2", "Fitting chi^{2}">,
                            Value<double, "t0", "Vertex time">,
                            Value<stdx::array3f, "x0", "Vertex position">,
                            Value<float, "Ek0", "Vertex kinetic energy">,
                            Value<stdx::array3f, "p0", "Vertex momentum">,
                            Value<stdx::array2f, "c0", "Transverse center">,
                            Value<float, "r0", "Transverse radius">,
                            Value<float, "z0", "Reference Z">,
                            Value<float, "phi0", "Reference azimuth angle">,
                            Value<float, "theta0", "Reference zenith angle">>;

constexpr auto CalculateHelix(TupleContain<CDCTrack> auto& track);
constexpr auto CalculateVertex(TupleContain<CDCTrack> auto& track);

} // namespace MACE::Data
