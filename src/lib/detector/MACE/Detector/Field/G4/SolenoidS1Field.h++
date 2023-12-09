#pragma once

#include "MACE/Detector/Field/SolenoidS1Field.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::Detector::Field::G4 {

class SolenoidS1Field : public WrapAsG4Field<Field::SolenoidS1Field> {
public:
    SolenoidS1Field();
};

} // namespace MACE::Detector::Field::G4
