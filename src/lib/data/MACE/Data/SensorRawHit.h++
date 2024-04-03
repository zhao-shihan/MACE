#pragma once

#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"

namespace MACE::Data {

using TTCSiPMRawHit = TupleModel<Value<short, "TileID", "Hit detector ID">,
                                 Value<double, "t", "Optical photon hit time">>;

using EMCPMTRawHit = TupleModel<Value<short, "UnitID", "Hit unit ID">,
                                Value<double, "t", "Optical photon hit time">>;

} // namespace MACE::Data
