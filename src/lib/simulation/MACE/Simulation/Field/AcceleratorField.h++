#pragma once

#include "MACE/Detector/Field/AcceleratorField.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::inline Simulation::inline Field {

class AcceleratorField : public Detector::Field::WrapAsG4Field<Detector::Field::AcceleratorField> {
public:
    AcceleratorField();

    virtual auto DoesFieldChangeEnergy() const -> G4bool override { return true; }
};

} // namespace MACE::inline Simulation::inline Field
