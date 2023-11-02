#pragma once

#include "MACE/Data/Field.h++"
#include "MACE/Data/Model.h++"

namespace MACE::Data {

using SimDataBasis = Model<Field<int, "mcEvtID", "MC Event ID">,
                           Field<int, "mcTrkID", "MC Track ID">,
                           Field<int, "mcPdgID", "Particle PDG ID (MC Truth)">>;

} // namespace MACE::Data
