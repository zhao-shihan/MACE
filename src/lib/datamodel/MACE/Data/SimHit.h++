#pragma once

#include "MACE/Data/Hit.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Utility/FixedString.h++"

namespace MACE::Data {

using SimHitBasicTruth = TupleModel<Value<int, "EvtID", "MC Event ID">,
                                    Value<int, "TrkID", "MC Track ID">,
                                    Value<int, "PDGID", "Particle PDG ID (MC truth)">>;

using SimHitVertexTruth = TupleModel<Value<float, "t0", "Vertex time (MC truth)">,
                                     Value<stdx::array3f, "x0", "Vertex position (MC truth)">,
                                     Value<float, "Ek0", "Vertex kinetic energy (MC truth)">,
                                     Value<stdx::array3f, "p0", "Vertex momentum (MC truth)">,
                                     Value<String31, "CreatProc", "Track creator process (MC truth)">>;

using CDCSimHit = TupleModel<CDCHit,
                             SimHitBasicTruth,
                             Value<float, "Ek", "Hitting kinetic energy (MC truth)">,
                             Value<stdx::array3f, "x", "Hitting position (MC truth)">,
                             Value<stdx::array3f, "p", "Hitting momentum (MC truth)">,
                             SimHitVertexTruth>;

using EMCSimHit = TupleModel<EMCHit,
                             SimHitBasicTruth,
                             Value<float, "Ek", "Hitting kinetic energy (MC truth)">,
                             Value<stdx::array3f, "x", "Hitting position (MC truth)">,
                             Value<stdx::array3f, "p", "Hitting momentum (MC truth)">,
                             SimHitVertexTruth>;

using MCPSimHit = TupleModel<MCPHit,
                             SimHitBasicTruth,
                             Value<float, "Ek", "Hitting kinetic energy (MC truth)">,
                             Value<stdx::array3f, "p", "Hitting momentum (MC truth)">,
                             SimHitVertexTruth>;

} // namespace MACE::Data
