#pragma once

#include "CLHEP/Vector/TwoVector.h"

#include <memory>
#include <new>
#include <type_traits>

namespace MACE::Utility::CLHEPVectorX::Hep2VectorData {

inline double* operator&(CLHEP::Hep2Vector& twoVector) noexcept;
inline const double* operator&(const CLHEP::Hep2Vector& twoVector) noexcept;
inline double* operator&(CLHEP::Hep2Vector&& twoVector) noexcept = delete;
inline const double* operator&(const CLHEP::Hep2Vector&& twoVector) noexcept = delete;

} // namespace MACE::Utility::CLHEPVectorX::Hep2VectorData

#include "MACE/Utility/CLHEPVectorX/Hep2VectorData.inl"
