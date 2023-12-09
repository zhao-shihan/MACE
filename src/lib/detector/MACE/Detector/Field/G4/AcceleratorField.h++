#pragma once

#include "MACE/Detector/Field/AcceleratorField.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::Detector::Field::G4 {

class AcceleratorField : public WrapAsG4Field<Field::AcceleratorField> {
public:
    AcceleratorField();

    virtual auto DoesFieldChangeEnergy() const -> G4bool override { return true; }
};

} // namespace MACE::Detector::Field::G4
