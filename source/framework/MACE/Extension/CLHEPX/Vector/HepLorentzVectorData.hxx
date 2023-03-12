#pragma once

#include "MACE/Extension/CLHEPX/Vector/Hep3VectorData.hxx"
#include "MACE/Extension/CLHEPX/Vector/internal/ForbiddenLore.hxx"

#include "CLHEP/Vector/LorentzVector.h"

#include <new>
#include <type_traits>

namespace MACE::inline Extension::CLHEPX::Vector::HepLorentzVectorData {

constexpr double* operator&(CLHEP::HepLorentzVector& vector) noexcept;
constexpr const double* operator&(const CLHEP::HepLorentzVector& vector) noexcept;
constexpr double* operator&(CLHEP::HepLorentzVector&& vector) noexcept = delete;
constexpr const double* operator&(const CLHEP::HepLorentzVector&& vector) noexcept = delete;

} // namespace MACE::inline Extension::CLHEPX::Vector::HepLorentzVectorData

#include "MACE/Extension/CLHEPX/Vector/HepLorentzVectorData.inl"
