#pragma once

#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Extension/stdx/arraynx.h++"

#include <vector>

namespace MACE::Data {

using SimDecayVertex = MACE::Data::TupleModel<Data::Value<int, "EvtID", "MC Event ID">,
                                              Data::Value<int, "TrkID", "Parent MC Track ID">,
                                              Data::Value<int, "PDGID", "Parent PDG ID">,
                                              Data::Value<std::vector<int>, "SecPDGID", "PDG ID of decay products">,
                                              Data::Value<double, "t", "Decay time">,
                                              Data::Value<stdx::array3f, "x", "Decay position">,
                                              Data::Value<float, "Ek", "Parent kinetic energy at decay">,
                                              Data::Value<stdx::array3f, "p", "Parent momentum at decay">>;

}; // namespace MACE::Data
