#pragma once

#include "MACE/Detector/Field/EMCField.h++"
#include "MACE/Detector/Field/WrapAsG4Field.h++"

namespace MACE::Detector::Field::G4 {

class EMCField : public WrapAsG4Field<Field::EMCField> {
public:
    EMCField();
};

} // namespace MACE::Detector::Field::G4
