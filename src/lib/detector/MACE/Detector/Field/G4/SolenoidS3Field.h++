#pragma once

#include "MACE/Detector/Field/SolenoidS3Field.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::Detector::Field::G4 {

class SolenoidS3Field : public WrapAsG4Field<Field::SolenoidS3Field<G4double>> {
public:
    SolenoidS3Field();
};

} // namespace MACE::Detector::Field::G4
