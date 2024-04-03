#pragma once

#include "MACE/Data/RawHit.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"

namespace MACE::Data {

namespace internal {

using HitEventIDHitID = TupleModel<Value<int, "EvtID", "Event ID">,
                                   Value<int, "HitID", "Hit ID">>;

} // namespace internal

using CDCHit = TupleModel<internal::HitEventIDHitID,
                          CDCRawHit,
                          Value<float, "tD", "Drift time">,
                          Value<float, "d", "Drift distance">>;

using TTCHit = TupleModel<internal::HitEventIDHitID,
                          TTCRawHit>;

using MCPHit = TupleModel<internal::HitEventIDHitID,
                          MCPRawHit>;

using EMCHit = TupleModel<internal::HitEventIDHitID,
                          EMCRawHit>;

} // namespace MACE::Data
