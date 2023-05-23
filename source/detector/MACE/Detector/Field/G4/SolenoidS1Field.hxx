#pragma once

#include "MACE/Detector/Field/SolenoidS1Field.hxx"
#include "MACE/Detector/Field/WrapAsG4Field.hxx"

namespace MACE::Detector::Field::G4 {

class SolenoidS1Field final : public WrapAsG4Field<Field::SolenoidS1Field<G4double>> {
public:
    SolenoidS1Field();
};

} // namespace MACE::Detector::Field::G4
