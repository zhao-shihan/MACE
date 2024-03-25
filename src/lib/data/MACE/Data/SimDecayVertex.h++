#pragma once

#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Extension/stdx/arraynx.h++"

#include <vector>

namespace MACE::Data {

using SimDecayVertex = MACE::Data::TupleModel<MACE::Data::Value<int, "EvtID", "MC Event ID">,
                                              MACE::Data::Value<int, "TrkID", "Parent MC Track ID">,
                                              MACE::Data::Value<int, "PDGID", "Parent PDG ID">,
                                              MACE::Data::Value<std::vector<int>, "SecPDGID", "PDG ID of decay products">,
                                              MACE::Data::Value<double, "t", "Decay time">,
                                              MACE::Data::Value<stdx::array3f, "x", "Decay position">,
                                              MACE::Data::Value<float, "Ek", "Parent kinetic energy at decay">,
                                              MACE::Data::Value<stdx::array3f, "p", "Parent momentum at decay">>;

}; // namespace MACE::Data
