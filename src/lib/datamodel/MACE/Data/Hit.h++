#pragma once

#include "MACE/Data/RawHit.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Extension/stdx/arraynx.h++"

namespace MACE::Data {

using CDCHit = TupleModel<CDCRawHit,
                          Value<double, "tD", "Drift time">,
                          Value<float, "d", "Drift distance">>;

using EMCHit = TupleModel<Value<int, "UnitID", "Hitting unit ID">,
                          Value<double, "t", "Hitting time">,
                          Value<float, "E", "Energy deposition">>;

using MCPHit = TupleModel<Value<double, "t", "Hitting time">,
                          Value<stdx::array2f, "x", "Hitting position">>;

} // namespace MACE::Data
