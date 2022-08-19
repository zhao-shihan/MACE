#pragma once

#include "MACE/Utility/CLHEPVectorX/Hep3VectorData.hxx"
#include "MACE/Utility/CLHEPVectorX/internal/ForbiddenLore.hxx"

#include "CLHEP/Vector/LorentzVector.h"

#include <new>
#include <type_traits>

namespace MACE::Utility::CLHEPVectorX::HepLorentzVectorData {

constexpr double* operator&(CLHEP::HepLorentzVector& vector) noexcept;
constexpr const double* operator&(const CLHEP::HepLorentzVector& vector) noexcept;
constexpr double* operator&(CLHEP::HepLorentzVector&& vector) noexcept = delete;
constexpr const double* operator&(const CLHEP::HepLorentzVector&& vector) noexcept = delete;

} // namespace MACE::Utility::CLHEPVectorX::HepLorentzVectorData

#include "MACE/Utility/CLHEPVectorX/HepLorentzVectorData.inl"
