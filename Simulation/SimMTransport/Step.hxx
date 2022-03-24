#pragma once

#include "Global.hxx"

#include "TEveVector.h"

namespace MACE::Simulation::SimMTransport {

struct Step {
    double preTime;
    double postTime;
    TEveVectorD prePosition;
    TEveVectorD postPosition;
    TEveVectorD velocity;

    Step();
    Step(const Step&) = delete;
    Step& operator=(const Step&) = delete;
    bool operator==(const Step& rhs) { return this == &rhs; }
};

} // namespace MACE::Simulation::SimMTransport
