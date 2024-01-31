#pragma once

#include "MACE/Detector/Field/SolenoidB1Field.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class SolenoidB1Field : public Detector::Field::WrapAsG4Field<Detector::Field::SolenoidB1Field> {
public:
    SolenoidB1Field();
};

} // namespace MACE::inline Simulation::inline Field
