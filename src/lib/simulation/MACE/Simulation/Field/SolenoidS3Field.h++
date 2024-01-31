#pragma once

#include "MACE/Detector/Field/SolenoidS3Field.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class SolenoidS3Field : public Detector::Field::WrapAsG4Field<Detector::Field::SolenoidS3Field> {
public:
    SolenoidS3Field();
};

} // namespace MACE::inline Simulation::inline Field
