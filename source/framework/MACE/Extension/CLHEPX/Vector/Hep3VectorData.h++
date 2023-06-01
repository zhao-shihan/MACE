#pragma once

#include "MACE/Extension/CLHEPX/Vector/internal/ForbiddenLore.h++"

#include "CLHEP/Vector/ThreeVector.h"

#include <type_traits>

namespace MACE::inline Extension::CLHEPX::Vector::Hep3VectorData {

constexpr double* operator&(CLHEP::Hep3Vector& vector) noexcept;
constexpr const double* operator&(const CLHEP::Hep3Vector& vector) noexcept;
constexpr double* operator&(CLHEP::Hep3Vector&& vector) noexcept = delete;
constexpr const double* operator&(const CLHEP::Hep3Vector&& vector) noexcept = delete;

} // namespace MACE::inline Extension::CLHEPX::Vector::Hep3VectorData

#include "MACE/Extension/CLHEPX/Vector/Hep3VectorData.inl"
