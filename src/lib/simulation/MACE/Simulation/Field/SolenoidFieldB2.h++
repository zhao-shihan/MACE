#pragma once

#include "MACE/Detector/Field/SolenoidFieldB2.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class SolenoidFieldB2 : public Detector::Field::WrapAsG4Field<Detector::Field::SolenoidFieldB2> {
public:
    SolenoidFieldB2();
};

} // namespace MACE::inline Simulation::inline Field
