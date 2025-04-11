#pragma once

#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

namespace MACE::PhaseI::Data {

using SimPrimaryVertex = Mustard::Data::TupleModel<
    Mustard::Data::Value<int, "EvtID", "MC Event ID">,
    Mustard::Data::Value<int, "PDGID", "PDG ID">,
    Mustard::Data::Value<double, "t0", "Primary time">,
    Mustard::Data::Value<muc::array3f, "x0", "Primary position">,
    Mustard::Data::Value<float, "Ek0", "Primary kinetic energy">,
    Mustard::Data::Value<muc::array3f, "p0", "Primary momentum">>;

using SciFiVertex = Mustard::Data::TupleModel<
    Mustard::Data::Value<double, "Ek0", "Energy in vertex">,
    Mustard::Data::Value<muc::array3f, "p0", "Momentum in vertex">,
    Mustard::Data::Value<muc::array3f, "x0", "Produce position">>;

} // namespace MACE::PhaseI::Data
