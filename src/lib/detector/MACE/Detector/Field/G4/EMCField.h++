#pragma once

#include "MACE/Detector/Field/EMCField.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::Detector::Field::G4 {

class EMCField final : public WrapAsG4Field<Field::EMCField<G4double>> {
public:
    EMCField();
};

} // namespace MACE::Detector::Field::G4
