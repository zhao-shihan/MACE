#pragma once

#include "MACE/Detector/Field/ElectricField.hxx"
#include "MACE/Detector/Field/ElectromagneticField.hxx"
#include "MACE/Detector/Field/MagneticField.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"
#include "MACE/Utility/VectorCast.hxx"

#include "G4ElectricField.hh"
#include "G4ElectroMagneticField.hh"
#include "G4MagneticField.hh"

#include <algorithm>
#include <bit>
#include <type_traits>
#include <utility>

namespace MACE::Detector::Field {

template<ElectromagneticField<G4double> AField>
class WrapAsG4Field : public NonMoveableBase,
                      public std::conditional_t<MagneticField<AField, G4double>,
                                                G4MagneticField,
                                                std::conditional_t<ElectricField<AField, G4double>,
                                                                   G4ElectricField,
                                                                   G4ElectroMagneticField>>,
                      public AField {
public:
    using AField::AField;
    virtual ~WrapAsG4Field() = default;

    void GetFieldValue(const G4double* x, G4double* f) const override final;
    G4bool DoesFieldChangeEnergy() const override final { return not MagneticField<AField, G4double>; }
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/WrapAsG4Field.inl"
