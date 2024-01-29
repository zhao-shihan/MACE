#pragma once

#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Extension/stdx/arraynx.h++"

namespace MACE::Data {

using HitEventIDHitID = TupleModel<Value<int, "EvtID", "Event ID">,
                                   Value<int, "HitID", "Hit ID">>;

using CDCHit = TupleModel<HitEventIDHitID,
                          Value<int, "CellID", "Hit cell ID">,
                          Value<double, "t", "Signal time">,
                          Value<double, "tD", "Drift time">,
                          Value<float, "d", "Drift distance">,
                          Value<float, "Edep", "Energy deposition">>;

using EMCHit = TupleModel<HitEventIDHitID,
                          Value<int, "UnitID", "Hit unit ID">,
                          Value<double, "t", "Hit time">,
                          Value<float, "Edep", "Energy deposition">>;

using MCPHit = TupleModel<HitEventIDHitID,
                          Value<double, "t", "Hit time">,
                          Value<stdx::array2f, "x", "Hit position">>;

} // namespace MACE::Data
