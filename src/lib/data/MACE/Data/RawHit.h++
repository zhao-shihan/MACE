#pragma once

#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"

namespace MACE::Data {

namespace internal {

using HitEventIDHitID = TupleModel<Value<int, "EvtID", "Event ID">,
                                   Value<int, "HitID", "Hit ID">>;

} // namespace internal

using CDCRawHit = TupleModel<internal::HitEventIDHitID,
                             Value<short, "CellID", "Hit cell ID">,
                             Value<double, "t", "Signal time">,
                             Value<float, "Edep", "Energy deposition">>;

using TTCSiPMHit = TupleModel<internal::HitEventIDHitID,
                              Value<short, "DetID", "Hit detector ID">,
                              Value<double, "t", "Optical photon hit time">>;

using EMCPMTHit = TupleModel<internal::HitEventIDHitID,
                             Value<short, "UnitID", "Hit unit ID">,
                             Value<double, "t", "Optical photon hit time">>;

} // namespace MACE::Data
