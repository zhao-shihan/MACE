#pragma once

#include "MACE/Detector/Field/SpectrometerField.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::Detector::Field::G4 {

class SpectrometerField : public WrapAsG4Field<Field::SpectrometerField<G4double>> {
public:
    SpectrometerField();
};

} // namespace MACE::Detector::Field::G4
