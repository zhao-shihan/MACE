#pragma once

#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

namespace MACE::PhaseI::Data {

using SciFiSiPMRawHit = Mustard::Data::TupleModel<
    Mustard::Data::Value<int, "EvtID", "Event ID">,
    Mustard::Data::Value<int, "HitID", "Hit ID">,
    Mustard::Data::Value<short, "SiPMID", "Hit SiPM ID">,
    Mustard::Data::Value<double, "t", "Optical photon hit time">>;

using ECALPMRawHit = Mustard::Data::TupleModel<
    Mustard::Data::Value<short, "ModID", "Hit module ID">,
    Mustard::Data::Value<double, "t", "Optical photon hit time">>;
} // namespace MACE::PhaseI::Data
