#pragma once

#include "MACE/Detector/Field/SolenoidFieldS1.h++"
#include "MACE/Detector/Field/AsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class SolenoidFieldS1 : public Detector::Field::AsG4Field<Detector::Field::SolenoidFieldS1> {
public:
    SolenoidFieldS1();
};

} // namespace MACE::inline Simulation::inline Field
