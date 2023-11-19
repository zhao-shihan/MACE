#pragma once

#include "MACE/Data/Hit.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Extension/stdx/arraynx.h++"

namespace MACE::Data {

using SimHitBasis = TupleModel<Value<int, "EvtID", "MC Event ID">,
                               Value<int, "TrkID", "MC Track ID">,
                               Value<int, "PDGID", "Particle PDG ID (MC truth)">>;

using CDCSimHit = TupleModel<CDCHit,
                             SimHitBasis,
                             Value<float, "Ek", "Hitting kinetic energy (MC truth)">,
                             Value<stdx::array3f, "x", "Hitting position (MC truth)">,
                             Value<stdx::array3f, "p", "Hitting momentum (MC truth)">,
                             Value<float, "t0", "Vertex time (MC truth)">,
                             Value<stdx::array3f, "x0", "Vertex position (MC truth)">,
                             Value<float, "Ek0", "Vertex kinetic energy (MC truth)">,
                             Value<stdx::array3f, "p0", "Vertex momentum (MC truth)">>;

using EMCSimHit = TupleModel<EMCHit,
                             SimHitBasis,
                             Value<float, "Ek", "Hitting kinetic energy (MC truth)">,
                             Value<stdx::array3f, "x", "Hitting position (MC truth)">,
                             Value<stdx::array3f, "p", "Hitting momentum (MC truth)">,
                             Value<float, "t0", "Vertex time (MC truth)">,
                             Value<stdx::array3f, "x0", "Vertex position (MC truth)">,
                             Value<float, "Ek0", "Vertex kinetic energy (MC truth)">,
                             Value<stdx::array3f, "p0", "Vertex momentum (MC truth)">>;

using MCPSimHit = TupleModel<MCPHit,
                             SimHitBasis,
                             Value<float, "Ek", "Hitting kinetic energy (MC truth)">,
                             Value<stdx::array3f, "p", "Hitting momentum (MC truth)">,
                             Value<float, "t0", "Vertex time (MC truth)">,
                             Value<stdx::array3f, "x0", "Vertex position (MC truth)">,
                             Value<float, "Ek0", "Vertex kinetic energy (MC truth)">,
                             Value<stdx::array3f, "p0", "Vertex momentum (MC truth)">>;

} // namespace MACE::Data
