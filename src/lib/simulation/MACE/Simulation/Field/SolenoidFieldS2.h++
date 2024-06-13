#pragma once

#include "MACE/Detector/Field/SolenoidFieldS2.h++"
#include "MACE/Detector/Field/AsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class SolenoidFieldS2 : public Detector::Field::AsG4Field<Detector::Field::SolenoidFieldS2> {
public:
    SolenoidFieldS2();
};

} // namespace MACE::inline Simulation::inline Field
