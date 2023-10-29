#pragma once

#include "MACE/Data/Field.h++"
#include "MACE/Data/Model.h++"
#include "MACE/Extension/stdx/arraynx.h++"

namespace MACE::Data {

using CDCHit = Model<Field<int, "cellID", "Hitting cell ID">,
                     Field<float, "d", "Drift distance">,
                     Field<double, "t", "Hitting time">>;

using EMCHit = Model<Field<int, "unitID", "Hitting unit ID">,
                     Field<double, "t", "Hitting time">,
                     Field<float, "E", "Energy deposition">>;

using MCPHit = Model<Field<double, "t", "Hitting time">,
                     Field<stdx::array2f, "x", "Hitting position">>;

} // namespace MACE::Data
