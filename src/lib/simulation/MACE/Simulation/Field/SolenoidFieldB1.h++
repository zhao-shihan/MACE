#pragma once

#include "MACE/Detector/Field/SolenoidFieldB1.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class SolenoidFieldB1 : public Detector::Field::WrapAsG4Field<Detector::Field::SolenoidFieldB1> {
public:
    SolenoidFieldB1();
};

} // namespace MACE::inline Simulation::inline Field
