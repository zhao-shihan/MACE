#pragma once

#include "CLHEP/Vector/ThreeVector.h"

#include <memory>
#include <new>
#include <type_traits>

namespace MACE::Utility::CLHEPVectorX::Hep3VectorData {

inline double* operator&(CLHEP::Hep3Vector& threeVector) noexcept;
inline const double* operator&(const CLHEP::Hep3Vector& threeVector) noexcept;
inline double* operator&(CLHEP::Hep3Vector&& threeVector) noexcept = delete;
inline const double* operator&(const CLHEP::Hep3Vector&& threeVector) noexcept = delete;

} // namespace MACE::Utility::CLHEPVectorX::Hep3VectorData

#include "MACE/Utility/CLHEPVectorX/Hep3VectorData.inl"
