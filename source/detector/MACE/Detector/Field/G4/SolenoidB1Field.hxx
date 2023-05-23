#pragma once

#include "MACE/Detector/Field/SolenoidB1Field.hxx"
#include "MACE/Detector/Field/WrapAsG4Field.hxx"

namespace MACE::Detector::Field::G4 {

class SolenoidB1Field final : public WrapAsG4Field<Field::SolenoidB1Field<G4double>> {
public:
    SolenoidB1Field();
};

} // namespace MACE::Detector::Field::G4
