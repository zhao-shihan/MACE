#pragma once

#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"

namespace MACE::Data {

using CDCRawHit = TupleModel<Value<int, "CellID", "Hitting cell ID">,
                             Value<double, "t", "Signal time">>;

} // namespace MACE::Data
