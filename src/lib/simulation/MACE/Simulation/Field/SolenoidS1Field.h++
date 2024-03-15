#pragma once

#include "MACE/Detector/Field/SolenoidS1Field.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class SolenoidS1Field : public Detector::Field::WrapAsG4Field<Detector::Field::SolenoidS1Field> {
public:
    SolenoidS1Field();
};

} // namespace MACE::inline Simulation::inline Field
