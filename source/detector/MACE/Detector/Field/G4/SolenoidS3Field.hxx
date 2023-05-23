#pragma once

#include "MACE/Detector/Field/SolenoidS3Field.hxx"
#include "MACE/Detector/Field/WrapAsG4Field.hxx"

namespace MACE::Detector::Field::G4 {

class SolenoidS3Field final : public WrapAsG4Field<Field::SolenoidS3Field<G4double>> {
public:
    SolenoidS3Field();
};

} // namespace MACE::Detector::Field::G4
