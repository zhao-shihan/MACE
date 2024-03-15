#pragma once

#include "MACE/Detector/Field/SpectrometerField.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class SpectrometerField : public Detector::Field::WrapAsG4Field<Detector::Field::SpectrometerField> {
public:
    SpectrometerField();
};

} // namespace MACE::inline Simulation::inline Field
