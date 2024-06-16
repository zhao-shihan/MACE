#pragma once

#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

namespace MACE::Data {

using TTCSiPMRawHit = Mustard::Data::TupleModel<Mustard::Data::Value<short, "TileID", "Hit detector ID">,
                                 Mustard::Data::Value<double, "t", "Optical photon hit time">>;

using EMCPMTRawHit = Mustard::Data::TupleModel<Mustard::Data::Value<short, "UnitID", "Hit unit ID">,
                                Mustard::Data::Value<double, "t", "Optical photon hit time">>;

} // namespace MACE::Data
