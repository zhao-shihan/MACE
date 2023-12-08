#pragma once

#include "MACE/Detector/Field/SolenoidB2Field.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::Detector::Field::G4 {

class SolenoidB2Field : public WrapAsG4Field<Field::SolenoidB2Field<G4double>> {
public:
    SolenoidB2Field();
};

} // namespace MACE::Detector::Field::G4
