#pragma once

#include "Global.hh"
#include "Vector3.hh"

struct MACE::SimMTransport::Step {
    double_t preTime;
    double_t postTime;
    Vector3  prePosition;
    Vector3  postPosition;
    Vector3  velocity;

    Step();
    ~Step();
    Step(const Step&) = delete;
    Step& operator=(const Step&) = delete;
    bool operator==(const Step& rhs) { return this == &rhs; }
};
