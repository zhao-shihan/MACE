#pragma once

#include "MACE/Detector/Field/ElectricField.h++"
#include "MACE/Detector/Field/ElectromagneticField.h++"
#include "MACE/Detector/Field/MagneticField.h++"
#include "MACE/Utility/NonMoveableBase.h++"
#include "MACE/Utility/VectorCast.h++"

#include "G4ElectricField.hh"
#include "G4ElectroMagneticField.hh"
#include "G4MagneticField.hh"

#include "muc/array"

#include <algorithm>
#include <bit>
#include <type_traits>
#include <utility>

namespace MACE::Detector::Field {

namespace internal {

template<bool AChangeEnergy>
class G4EMFieldBase : public G4ElectroMagneticField {
public:
    auto DoesFieldChangeEnergy() const -> G4bool override final { return AChangeEnergy; }
};

} // namespace internal

template<ElectromagneticField AField, bool AEMFieldChangeEnergy = true>
class AsG4Field : public NonMoveableBase,
                  public std::conditional_t<MagneticField<AField>,
                                            G4MagneticField,
                                            std::conditional_t<ElectricField<AField>,
                                                               G4ElectricField,
                                                               internal::G4EMFieldBase<AEMFieldChangeEnergy>>>,
                  public AField {
public:
    using AField::AField;
    virtual ~AsG4Field() = default;

    auto GetFieldValue(const G4double* x, G4double* f) const -> void override final;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/AsG4Field.inl"
