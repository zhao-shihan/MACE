#pragma once

#include "MACE/Concept/Unordered.h++"

namespace MACE::Concept {

template<typename T>
concept NonComparable =
    requires(T& v, const T& cv) {
        requires not requires { v == cv; };
        requires not requires { cv == cv; };
        requires not requires { v != cv; };
        requires not requires { cv != cv; };
        requires Unordered<T>;
    };

} // namespace MACE::Concept
