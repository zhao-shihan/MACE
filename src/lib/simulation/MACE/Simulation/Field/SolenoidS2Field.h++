#pragma once

#include "MACE/Detector/Field/SolenoidS2Field.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class SolenoidS2Field : public Detector::Field::WrapAsG4Field<Detector::Field::SolenoidS2Field> {
public:
    SolenoidS2Field();
};

} // namespace MACE::inline Simulation::inline Field
