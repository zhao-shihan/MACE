#pragma once

#include "MACE/CLHEPX/Vector/internal/ForbiddenLore.hxx"

#include "CLHEP/Vector/TwoVector.h"

#include <new>
#include <type_traits>

namespace MACE::CLHEPX::Vector::Hep2VectorData {

constexpr double* operator&(CLHEP::Hep2Vector& vector) noexcept;
constexpr const double* operator&(const CLHEP::Hep2Vector& vector) noexcept;
constexpr double* operator&(CLHEP::Hep2Vector&& vector) noexcept = delete;
constexpr const double* operator&(const CLHEP::Hep2Vector&& vector) noexcept = delete;

} // namespace MACE::CLHEPX::Vector::Hep2VectorData

#include "MACE/CLHEPX/Vector/Hep2VectorData.inl"
