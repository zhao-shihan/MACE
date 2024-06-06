#pragma once

#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"

#include "muc/array"

namespace MACE::Data {

using CDCRawHit = TupleModel<Value<short, "CellID", "Hit cell ID">,
                             Value<double, "t", "Signal time">,
                             Value<float, "Edep", "Energy deposition">>;

using TTCRawHit = TupleModel<Value<short, "TileID", "Hit detector ID">,
                             Value<double, "t", "Hit time">,
                             Value<float, "Edep", "Energy deposition">>;

using MCPRawHit = TupleModel<Value<double, "t", "Hit time">,
                             Value<muc::array2f, "x", "Hit position">>;

using EMCRawHit = TupleModel<Value<short, "UnitID", "Hit unit ID">,
                             Value<double, "t", "Hit time">,
                             Value<float, "Edep", "Energy deposition">>;

} // namespace MACE::Data
