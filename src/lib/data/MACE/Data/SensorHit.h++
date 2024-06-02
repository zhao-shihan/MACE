#pragma once

#include "MACE/Data/SensorRawHit.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"

namespace MACE::Data {

namespace internal {

using HitEventIDHitID = TupleModel<Value<int, "EvtID", "Event ID">,
                                   Value<int, "HitID", "Hit ID">>;

} // namespace internal

using TTCSiPMHit = TupleModel<internal::HitEventIDHitID,
                              TTCSiPMRawHit>;

using EMCPMTHit = TupleModel<internal::HitEventIDHitID,
                             EMCPMTRawHit,
                             Value<double, "lambda", "Wavelength of the photon">>;

} // namespace MACE::Data
