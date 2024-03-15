#pragma once

#include "MACE/Detector/Field/SolenoidB2Field.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class SolenoidB2Field : public Detector::Field::WrapAsG4Field<Detector::Field::SolenoidB2Field> {
public:
    SolenoidB2Field();
};

} // namespace MACE::inline Simulation::inline Field
