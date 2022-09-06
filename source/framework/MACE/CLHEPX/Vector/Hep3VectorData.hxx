#pragma once

#include "MACE/CLHEPX/Vector/internal/ForbiddenLore.hxx"

#include "CLHEP/Vector/ThreeVector.h"

#include <type_traits>

namespace MACE::CLHEPX::Vector::Hep3VectorData {

constexpr double* operator&(CLHEP::Hep3Vector& vector) noexcept;
constexpr const double* operator&(const CLHEP::Hep3Vector& vector) noexcept;
constexpr double* operator&(CLHEP::Hep3Vector&& vector) noexcept = delete;
constexpr const double* operator&(const CLHEP::Hep3Vector&& vector) noexcept = delete;

} // namespace MACE::CLHEPX::Vector::Hep3VectorData

#include "MACE/CLHEPX/Vector/Hep3VectorData.inl"
