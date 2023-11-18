#pragma once

#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Extension/stdx/arraynx.h++"

namespace MACE::Data {

using CDCHit = TupleModel<Value<int, "cellID", "Hitting cell ID">,
                          Value<float, "d", "Drift distance">,
                          Value<double, "t", "Hitting time">>;

using EMCHit = TupleModel<Value<int, "unitID", "Hitting unit ID">,
                          Value<double, "t", "Hitting time">,
                          Value<float, "E", "Energy deposition">>;

using MCPHit = TupleModel<Value<double, "t", "Hitting time">,
                          Value<stdx::array2f, "x", "Hitting position">>;

} // namespace MACE::Data
