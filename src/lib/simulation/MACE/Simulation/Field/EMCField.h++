#pragma once

#include "MACE/Detector/Field/EMCField.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class EMCField : public Detector::Field::WrapAsG4Field<Detector::Field::EMCField> {
public:
    EMCField();
};

} // namespace MACE::inline Simulation::inline Field
