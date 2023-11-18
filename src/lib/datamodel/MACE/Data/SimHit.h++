#pragma once

#include "MACE/Data/Hit.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Extension/stdx/arraynx.h++"

namespace MACE::Data {

using SimHitBasis = TupleModel<Value<int, "evtID", "MC Event ID">,
                               Value<int, "trkID", "MC Track ID">,
                               Value<int, "pdgID", "Particle PDG ID (MC truth)">,
                               Value<float, "Ek", "Hitting kinetic energy (MC truth)">,
                               Value<stdx::array3f, "p", "Hitting momentum (MC truth)">,
                               Value<float, "t0", "Vertex time (MC truth)">,
                               Value<stdx::array3f, "x0", "Vertex position (MC truth)">,
                               Value<float, "Ek0", "Vertex kinetic energy (MC truth)">,
                               Value<stdx::array3f, "p0", "Vertex momentum (MC truth)">>;

using CDCSimHit = TupleModel<CDCHit, SimHitBasis>;

using EMCSimHit = TupleModel<EMCHit, SimHitBasis>;

using MCPSimHit = TupleModel<MCPHit, SimHitBasis>;

} // namespace MACE::Data
