#pragma once

#include "MACE/Detector/Field/SpectrometerField.hxx"
#include "MACE/Detector/Field/WrapAsG4Field.hxx"

namespace MACE::Detector::Field::G4 {

class SpectrometerField final : public WrapAsG4Field<Field::SpectrometerField<G4double>> {
public:
    SpectrometerField();
};

} // namespace MACE::Detector::Field::G4
