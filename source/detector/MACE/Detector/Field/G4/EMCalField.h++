#pragma once

#include "MACE/Detector/Field/EMCalField.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::Detector::Field::G4 {

class EMCalField final : public WrapAsG4Field<Field::EMCalField<G4double>> {
public:
    EMCalField();
};

} // namespace MACE::Detector::Field::G4
