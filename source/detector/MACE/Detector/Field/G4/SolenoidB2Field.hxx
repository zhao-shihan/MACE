#pragma once

#include "MACE/Detector/Field/SolenoidB2Field.hxx"
#include "MACE/Detector/Field/WrapAsG4Field.hxx"

namespace MACE::Detector::Field::G4 {

class SolenoidB2Field final : public WrapAsG4Field<Field::SolenoidB2Field<G4double>> {
public:
    SolenoidB2Field();
};

} // namespace MACE::Detector::Field::G4
