#pragma once

#include "CLHEP/Vector/TwoVector.h"

#include <memory>
#include <new>
#include <type_traits>

namespace MACE::Utility::CLHEPHep2VectorData {

inline double* operator&(CLHEP::Hep2Vector& twoVector) noexcept;
inline const double* operator&(const CLHEP::Hep2Vector& twoVector) noexcept;
inline double* operator&(CLHEP::Hep2Vector&& twoVector) noexcept = delete;
inline const double* operator&(const CLHEP::Hep2Vector&& twoVector) noexcept = delete;

} // namespace MACE::Utility::CLHEPHep2VectorData

#include "MACE/Utility/CLHEPHep2VectorData.inl"
