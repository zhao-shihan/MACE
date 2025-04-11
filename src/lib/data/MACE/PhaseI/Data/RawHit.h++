#pragma once

#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

#include "muc/array"

namespace MACE::PhaseI::Data {

using SciFiRawHit = Mustard::Data::TupleModel<
    Mustard::Data::Value<int, "FibreID", "Fibre ID">,
    Mustard::Data::Value<double, "t", "Hit time">,
    Mustard::Data::Value<float, "Edep", "Energy deposition">>;

} // namespace MACE::PhaseI::Data
