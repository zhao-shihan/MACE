#pragma once

#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

namespace MACE::Data {

using TTCSiPMRawHit = Mustard::Data::TupleModel<
    Mustard::Data::Value<short, "TileID", "Hit detector ID">,
    Mustard::Data::Value<double, "t", "Optical photon hit time">>;

using ECALPMRawHit = Mustard::Data::TupleModel<
    Mustard::Data::Value<short, "ModID", "Hit module ID">,
    Mustard::Data::Value<double, "t", "Optical photon hit time">>;

using VetoPMRawHit = Mustard::Data::TupleModel<
    Mustard::Data::Value<short, "StripID", "Hit strip ID">,
    Mustard::Data::Value<double, "t", "Optical photon hit time">,
    Mustard::Data::Value<short, "LocalSiPMID", "Hitted SiPM ID in a strip">>;


} // namespace MACE::Data
