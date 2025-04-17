#pragma once

#include "MACE/PhaseI/Data/SensorRawHit.h++"

#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

namespace MACE::PhaseI::Data {

namespace internal {
using HitEventIDHitID = Mustard::Data::TupleModel<
    Mustard::Data::Value<int, "EvtID", "Event ID">,
    Mustard::Data::Value<int, "HitID", "Hit ID">>;

} // namespace internal

using SciFiSiPMHit = Mustard::Data::TupleModel<
    SciFiSiPMRawHit>;

using SiPMHit = Mustard::Data::TupleModel<
    Mustard::Data::Value<int, "EvtID", "Event ID">,
    Mustard::Data::Value<int, "nOptPho", "Number of photon hit">,
    Mustard::Data::Value<int, "SiPMID", "SiPM ID">,
    Mustard::Data::Value<double, "t", "Time over threshold">>;

} // namespace MACE::PhaseI::Data
