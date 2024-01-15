#pragma once

#include "MACE/Detector/Field/SolenoidB1Field.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::Detector::Field::G4 {

class SolenoidB1Field : public WrapAsG4Field<Field::SolenoidB1Field> {
public:
    SolenoidB1Field();
};

} // namespace MACE::Detector::Field::G4
