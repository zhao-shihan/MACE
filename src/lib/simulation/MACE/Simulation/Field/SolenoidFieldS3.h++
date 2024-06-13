#pragma once

#include "MACE/Detector/Field/SolenoidFieldS3.h++"
#include "MACE/Detector/Field/AsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class SolenoidFieldS3 : public Detector::Field::AsG4Field<Detector::Field::SolenoidFieldS3> {
public:
    SolenoidFieldS3();
};

} // namespace MACE::inline Simulation::inline Field
