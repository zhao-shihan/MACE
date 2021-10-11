#pragma once

#include "Global.hh"
#include "CLHEP/Vector/ThreeVector.h"

struct MACE::SimMTransport::Step {
    double_t preTime;
    double_t postTime;
    CLHEP::Hep3Vector prePosition;
    CLHEP::Hep3Vector postPosition;
    CLHEP::Hep3Vector velocity;

    Step();
    ~Step();
    Step(const Step&) = delete;
    Step& operator=(const Step&) = delete;
    bool operator==(const Step& rhs) { return this == &rhs; }
};
