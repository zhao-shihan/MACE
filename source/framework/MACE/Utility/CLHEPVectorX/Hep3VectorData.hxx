#pragma once

#include "MACE/Utility/CLHEPVectorX/internal/ForbiddenLore.hxx"

#include "CLHEP/Vector/ThreeVector.h"

#include <type_traits>

namespace MACE::Utility::CLHEPVectorX::Hep3VectorData {

constexpr double* operator&(CLHEP::Hep3Vector& vector) noexcept;
constexpr const double* operator&(const CLHEP::Hep3Vector& vector) noexcept;
constexpr double* operator&(CLHEP::Hep3Vector&& vector) noexcept = delete;
constexpr const double* operator&(const CLHEP::Hep3Vector&& vector) noexcept = delete;

} // namespace MACE::Utility::CLHEPVectorX::Hep3VectorData

#include "MACE/Utility/CLHEPVectorX/Hep3VectorData.inl"
