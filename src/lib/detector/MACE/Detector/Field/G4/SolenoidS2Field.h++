#pragma once

#include "MACE/Detector/Field/SolenoidS2Field.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::Detector::Field::G4 {

class SolenoidS2Field : public WrapAsG4Field<Field::SolenoidS2Field<G4double>> {
public:
    SolenoidS2Field();
};

} // namespace MACE::Detector::Field::G4
