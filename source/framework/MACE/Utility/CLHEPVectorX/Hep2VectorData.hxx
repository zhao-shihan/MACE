#pragma once

#include "MACE/Utility/CLHEPVectorX/internal/ForbiddenLore.hxx"

#include "CLHEP/Vector/TwoVector.h"

#include <new>
#include <type_traits>

namespace MACE::Utility::CLHEPVectorX::Hep2VectorData {

constexpr double* operator&(CLHEP::Hep2Vector& vector) noexcept;
constexpr const double* operator&(const CLHEP::Hep2Vector& vector) noexcept;
constexpr double* operator&(CLHEP::Hep2Vector&& vector) noexcept = delete;
constexpr const double* operator&(const CLHEP::Hep2Vector&& vector) noexcept = delete;

} // namespace MACE::Utility::CLHEPVectorX::Hep2VectorData

#include "MACE/Utility/CLHEPVectorX/Hep2VectorData.inl"
