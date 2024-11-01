#pragma once

#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

#include "muc/array"

namespace MACE::Data {

using CDCRawHit = Mustard::Data::TupleModel<
    Mustard::Data::Value<short, "CellID", "Hit cell ID">,
    Mustard::Data::Value<double, "t", "Signal time">,
    Mustard::Data::Value<float, "Edep", "Energy deposition">>;

using TTCRawHit = Mustard::Data::TupleModel<
    Mustard::Data::Value<short, "TileID", "Hit detector ID">,
    Mustard::Data::Value<double, "t", "Hit time">,
    Mustard::Data::Value<float, "Edep", "Energy deposition">>;

using MCPRawHit = Mustard::Data::TupleModel<
    Mustard::Data::Value<double, "t", "Hit time">,
    Mustard::Data::Value<muc::array2f, "x", "Hit position">>;

using ECALRawHit = Mustard::Data::TupleModel<
    Mustard::Data::Value<short, "ModID", "Hit module ID">,
    Mustard::Data::Value<double, "t", "Hit time">,
    Mustard::Data::Value<float, "Edep", "Energy deposition">>;

} // namespace MACE::Data
