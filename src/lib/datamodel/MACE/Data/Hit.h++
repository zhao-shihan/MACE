#pragma once

#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Extension/stdx/arraynx.h++"

namespace MACE::Data {

namespace internal {

using HitEventIDHitID = TupleModel<Value<int, "EvtID", "Event ID">,
                                   Value<int, "HitID", "Hit ID">>;

} // namespace internal

using CDCHit = TupleModel<internal::HitEventIDHitID,
                          Value<short, "CellID", "Hit cell ID">,
                          Value<double, "t", "Signal time">,
                          Value<float, "tD", "Drift time">,
                          Value<float, "d", "Drift distance">,
                          Value<float, "Edep", "Energy deposition">>;

using STCHit = TupleModel<internal::HitEventIDHitID,
                          Value<short, "DetID", "Hit detector ID">,
                          Value<double, "t", "Hit time">,
                          Value<float, "Edep", "Energy deposition">>;

using STCSiPMHit = TupleModel<internal::HitEventIDHitID,
                              Value<short, "DetID", "Hit detector ID">,
                              Value<double, "t", "Hit time">>;

using MCPHit = TupleModel<internal::HitEventIDHitID,
                          Value<double, "t", "Hit time">,
                          Value<stdx::array2f, "x", "Hit position">>;

using EMCHit = TupleModel<internal::HitEventIDHitID,
                          Value<short, "UnitID", "Hit unit ID">,
                          Value<double, "t", "Hit time">,
                          Value<float, "Edep", "Energy deposition">>;

using EMCPMTHit = TupleModel<internal::HitEventIDHitID,
                             Value<short, "UnitID", "Hit unit ID">,
                             Value<double, "t", "Hit time">>;

} // namespace MACE::Data
