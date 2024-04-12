#pragma once

#include "MACE/Detector/Field/SolenoidFieldS3.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class SolenoidFieldS3 : public Detector::Field::WrapAsG4Field<Detector::Field::SolenoidFieldS3> {
public:
    SolenoidFieldS3();
};

} // namespace MACE::inline Simulation::inline Field
