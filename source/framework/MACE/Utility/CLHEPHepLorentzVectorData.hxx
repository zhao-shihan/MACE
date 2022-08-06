#pragma once

#include "CLHEP/Vector/LorentzVector.h"

#include <memory>
#include <new>
#include <type_traits>

namespace MACE::Utility::CLHEPHepLorentzVectorData {

inline double* operator&(CLHEP::HepLorentzVector& fourVector) noexcept;
inline const double* operator&(const CLHEP::HepLorentzVector& fourVector) noexcept;
inline double* operator&(CLHEP::HepLorentzVector&& fourVector) noexcept = delete;
inline const double* operator&(const CLHEP::HepLorentzVector&& fourVector) noexcept = delete;

} // namespace MACE::Utility::CLHEPHepLorentzVectorData

#include "MACE/Utility/CLHEPHepLorentzVectorData.inl"
