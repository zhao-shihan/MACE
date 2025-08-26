#pragma once

#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

#include "muc/array"

namespace MACE::PhaseI::Data {

using SciFiRawHit = Mustard::Data::TupleModel<
    Mustard::Data::Value<int, "FiberID", "Fiber ID">,
    Mustard::Data::Value<double, "t", "Hit time">,
    Mustard::Data::Value<float, "Edep", "Energy deposition">>;

using MRPCRawHit = Mustard::Data::TupleModel<
    Mustard::Data::Value<short, "ModID", "Hit module ID">,
    Mustard::Data::Value<double, "t", "Hit time">,
    Mustard::Data::Value<muc::array3f, "x", "Hit position">>;

using TTCRawHit = Mustard::Data::TupleModel<
    Mustard::Data::Value<short, "TileID", "Hit detector ID">,
    Mustard::Data::Value<double, "t", "Hit time">,
    Mustard::Data::Value<float, "Edep", "Energy deposition">>;

} // namespace MACE::PhaseI::Data
