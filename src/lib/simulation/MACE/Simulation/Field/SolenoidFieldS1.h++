#pragma once

#include "MACE/Detector/Field/SolenoidFieldS1.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class SolenoidFieldS1 : public Detector::Field::WrapAsG4Field<Detector::Field::SolenoidFieldS1> {
public:
    SolenoidFieldS1();
};

} // namespace MACE::inline Simulation::inline Field
