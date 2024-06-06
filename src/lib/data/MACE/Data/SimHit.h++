#pragma once

#include "MACE/Data/Hit.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/Value.h++"

#include "muc/array"

#include <string>

namespace MACE::Data {

namespace internal {

using SimHitVertexTruth = TupleModel<Value<int, "TrkID", "MC Track ID">,
                                     Value<int, "PDGID", "Particle PDG ID (MC truth)">,
                                     Value<double, "t0", "Vertex time (MC truth)">,
                                     Value<muc::array3f, "x0", "Vertex position (MC truth)">,
                                     Value<float, "Ek0", "Vertex kinetic energy (MC truth)">,
                                     Value<muc::array3f, "p0", "Vertex momentum (MC truth)">,
                                     Value<std::string, "CreatProc", "Track creator process (MC truth)">>;

} // namespace internal

using CDCSimHit = TupleModel<CDCHit,
                             Value<double, "tHit", "Hit time (MC truth)">,
                             Value<muc::array3f, "x", "Hit position (MC truth)">,
                             Value<float, "Ek", "Hit kinetic energy (MC truth)">,
                             Value<muc::array3f, "p", "Hit momentum (MC truth)">,
                             internal::SimHitVertexTruth>;

using TTCSimHit = TupleModel<TTCHit,
                             Value<int, "nOptPho", "Number of optical photon hits on SiPM (MC truth)">,
                             Value<muc::array3f, "x", "Hit position (MC truth)">,
                             Value<float, "Ek", "Hit kinetic energy (MC truth)">,
                             Value<muc::array3f, "p", "Hit momentum (MC truth)">,
                             internal::SimHitVertexTruth>;

using MCPSimHit = TupleModel<MCPHit,
                             Value<float, "Edep", "Energy deposition">,
                             Value<float, "Ek", "Hit kinetic energy (MC truth)">,
                             Value<muc::array3f, "p", "Hit momentum (MC truth)">,
                             internal::SimHitVertexTruth>;

using EMCSimHit = TupleModel<EMCHit,
                             Value<int, "nOptPho", "Number of optical photon hits on PMT (MC truth)">,
                             Value<muc::array3f, "x", "Hit position (MC truth)">,
                             Value<float, "Ek", "Hit kinetic energy (MC truth)">,
                             Value<muc::array3f, "p", "Hit momentum (MC truth)">,
                             internal::SimHitVertexTruth>;

} // namespace MACE::Data
