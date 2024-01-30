#pragma once

#include "MACE/Data/Hit.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Utility/FixedString.h++"

namespace MACE::Data {

using SimHitVertexTruth = TupleModel<Value<int, "TrkID", "MC Track ID">,
                                     Value<int, "PDGID", "Particle PDG ID (MC truth)">,
                                     Value<float, "t0", "Vertex time (MC truth)">,
                                     Value<stdx::array3f, "x0", "Vertex position (MC truth)">,
                                     Value<float, "Ek0", "Vertex kinetic energy (MC truth)">,
                                     Value<stdx::array3f, "p0", "Vertex momentum (MC truth)">,
                                     Value<String31, "CreatProc", "Track creator process (MC truth)">>;

using CDCSimHit = TupleModel<CDCHit,
                             Value<double, "tHit", "Hit time (MC truth)">,
                             Value<float, "Ek", "Hit kinetic energy (MC truth)">,
                             Value<stdx::array3f, "x", "Hit position (MC truth)">,
                             Value<stdx::array3f, "p", "Hit momentum (MC truth)">,
                             SimHitVertexTruth>;

using EMCSimHit = TupleModel<EMCHit,
                             Value<float, "Ek", "Hit kinetic energy (MC truth)">,
                             Value<stdx::array3f, "x", "Hit position (MC truth)">,
                             Value<stdx::array3f, "p", "Hit momentum (MC truth)">,
                             SimHitVertexTruth>;

using EMCPMTSimHit = TupleModel<EMCPMTHit /* , Value<int, "EMCHitID", "EMC Hit ID (MC truth)"> */>;

using MCPSimHit = TupleModel<MCPHit,
                             Value<float, "Ek", "Hit kinetic energy (MC truth)">,
                             Value<stdx::array3f, "p", "Hit momentum (MC truth)">,
                             SimHitVertexTruth>;

} // namespace MACE::Data
