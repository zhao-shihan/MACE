#pragma once

#include "Global.hh"
#include "TEveVector.h"

struct MACE::SimMTransport::Step {
    double_t preTime;
    double_t postTime;
    TEveVectorD prePosition;
    TEveVectorD postPosition;
    TEveVectorD velocity;

    Step();
    Step(const Step&) = delete;
    Step& operator=(const Step&) = delete;
    bool operator==(const Step& rhs) { return this == &rhs; }
};
