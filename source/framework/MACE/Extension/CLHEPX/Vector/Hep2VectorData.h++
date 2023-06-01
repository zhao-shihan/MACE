#pragma once

#include "MACE/Extension/CLHEPX/Vector/internal/ForbiddenLore.h++"

#include "CLHEP/Vector/TwoVector.h"

#include <new>
#include <type_traits>

namespace MACE::inline Extension::CLHEPX::Vector::Hep2VectorData {

constexpr double* operator&(CLHEP::Hep2Vector& vector) noexcept;
constexpr const double* operator&(const CLHEP::Hep2Vector& vector) noexcept;
constexpr double* operator&(CLHEP::Hep2Vector&& vector) noexcept = delete;
constexpr const double* operator&(const CLHEP::Hep2Vector&& vector) noexcept = delete;

} // namespace MACE::inline Extension::CLHEPX::Vector::Hep2VectorData

#include "MACE/Extension/CLHEPX/Vector/Hep2VectorData.inl"
