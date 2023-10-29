#pragma once

#include "MACE/Data/Field.h++"
#include "MACE/Data/Hit.h++"
#include "MACE/Data/Model.h++"
#include "MACE/Data/Model.h++"
#include "MACE/Data/SimDataBasis.h++"
#include "MACE/Extension/stdx/arraynx.h++"

namespace MACE::Data {

using SimHitBasis = Model<SimDataBasis,
                            Field<float, "Ek", "Hitting kinetic energy (MC truth)">,
                            Field<stdx::array3f, "p", "Hitting momentum (MC truth)">,
                            Field<float, "t0", "Vertex time (MC truth)">,
                            Field<stdx::array3f, "x0", "Vertex position (MC truth)">,
                            Field<float, "Ek0", "Vertex kinetic energy (MC truth)">,
                            Field<stdx::array3f, "p0", "Vertex momentum (MC truth)">>;

using CDCSimHit = Model<CDCHit, SimHitBasis>;

using EMCSimHit = Model<EMCHit, SimHitBasis>;

using MCPSimHit = Model<MCPHit, SimHitBasis>;

} // namespace MACE::Data
