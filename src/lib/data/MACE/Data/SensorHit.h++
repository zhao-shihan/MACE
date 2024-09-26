#pragma once

#include "MACE/Data/SensorRawHit.h++"

#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

namespace MACE::Data {

namespace internal {

using HitEventIDHitID = Mustard::Data::TupleModel<
    Mustard::Data::Value<int, "EvtID", "Event ID">,
    Mustard::Data::Value<int, "HitID", "Hit ID">>;

} // namespace internal

using TTCSiPMHit = Mustard::Data::TupleModel<
    internal::HitEventIDHitID,
    TTCSiPMRawHit>;

using ECALPMTHit = Mustard::Data::TupleModel<
    internal::HitEventIDHitID,
    ECALPMTRawHit>;

} // namespace MACE::Data
