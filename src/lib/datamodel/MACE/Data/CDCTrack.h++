#pragma once

#include "MACE/Data/Field.h++"
#include "MACE/Data/Model.h++"

namespace MACE::Data {

using CDCTrack = Model<Field<int, "pdgID", "Particle PDG ID">,
                         Field<int, "nHit", "Number of hits fitted">,
                         Field<float, "chi2", "Fitting chi^{2}">,
                         Field<double, "t0", "Vertex time">,
                         Field<std::array3f, "x0", "Vertex position">,
                         Field<float, "Ek0", "Vertex kinetic energy">,
                         Field<std::array3f, "p0", "Vertex momentum">,
                         Field<std::array2f, "c0", "Transverse center">,
                         Field<float, "r0", "Transverse radius">,
                         Field<float, "z0", "Reference Z">,
                         Field<float, "phi0", "Reference azimuth angle">,
                         Field<float, "theta0", "Reference zenith angle">>;

} // namespace MACE::Data
