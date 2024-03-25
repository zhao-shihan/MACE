#pragma once

#include "MACE/Detector/Field/MMSField.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class MMSField : public Detector::Field::WrapAsG4Field<Detector::Field::MMSField> {
public:
    MMSField();
};

} // namespace MACE::inline Simulation::inline Field
