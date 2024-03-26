#pragma once

#include "MACE/Data/RawHit.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Extension/stdx/arraynx.h++"

namespace MACE::Data {

using CDCHit = TupleModel<CDCRawHit,
                          Value<float, "tD", "Drift time">,
                          Value<float, "d", "Drift distance">>;

using TTCHit = TupleModel<internal::HitEventIDHitID,
                          Value<short, "DetID", "Hit detector ID">,
                          Value<double, "t", "Hit time">,
                          Value<float, "Edep", "Energy deposition">>;

using MCPHit = TupleModel<internal::HitEventIDHitID,
                          Value<double, "t", "Hit time">,
                          Value<stdx::array2f, "x", "Hit position">>;

using EMCHit = TupleModel<internal::HitEventIDHitID,
                          Value<short, "UnitID", "Hit unit ID">,
                          Value<double, "t", "Hit time">,
                          Value<float, "Edep", "Energy deposition">>;

} // namespace MACE::Data
