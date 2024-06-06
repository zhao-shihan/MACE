#pragma once

#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"

#include "muc/array"

#include <vector>

namespace MACE::Data {

using DecayVertex = MACE::Data::TupleModel<Data::Value<int, "EvtID", "Event ID">,
                                           Data::Value<int, "PDGID", "Parent PDG ID">,
                                           Data::Value<std::vector<int>, "SecPDGID", "PDG ID of decay products">,
                                           Data::Value<double, "t", "Decay time">,
                                           Data::Value<muc::array3f, "x", "Decay position">>;

} // namespace MACE::Data
