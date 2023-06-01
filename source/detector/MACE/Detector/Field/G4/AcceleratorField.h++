#pragma once

#include "MACE/Detector/Field/AcceleratorField.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::Detector::Field::G4 {

class AcceleratorField final : public WrapAsG4Field<Field::AcceleratorField<G4double>> {
public:
    AcceleratorField();
};

} // namespace MACE::Detector::Field::G4
