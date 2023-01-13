#pragma once

#include "CLHEP/Vector/TwoVector.h"

namespace MACE::inline Compatibility {

inline auto& operator/=(CLHEP::Hep2Vector& v, double c) {
    v[0] /= c;
    v[1] /= c;
    return v;
}

} // namespace MACE::inline Compatibility
