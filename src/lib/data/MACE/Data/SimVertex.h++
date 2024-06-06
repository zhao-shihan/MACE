#pragma once

#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Data/Vertex.h++"

#include "muc/array"

namespace MACE::Data {

using SimPrimaryVertex = MACE::Data::TupleModel<Data::Value<int, "EvtID", "MC Event ID">,
                                                Data::Value<int, "PDGID", "PDG ID">,
                                                Data::Value<double, "t0", "Primary time">,
                                                Data::Value<muc::array3f, "x0", "Primary position">,
                                                Data::Value<float, "Ek0", "Primary kinetic energy">,
                                                Data::Value<muc::array3f, "p0", "Primary momentum">>;

using SimDecayVertex = MACE::Data::TupleModel<DecayVertex,
                                              Data::Value<int, "TrkID", "Parent MC Track ID">,
                                              Data::Value<float, "Ek", "Parent kinetic energy at decay">,
                                              Data::Value<muc::array3f, "p", "Parent momentum at decay">>;

} // namespace MACE::Data
