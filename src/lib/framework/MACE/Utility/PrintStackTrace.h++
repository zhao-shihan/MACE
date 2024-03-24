#pragma once

#include "MACE/Utility/InlineMacro.h++"

#include <iostream>

namespace MACE::inline Utility {

MACE_NOINLINE auto PrintStackTrace(int depth = 64, int skip = 0, std::ostream& os = std::clog) -> void;

} // namespace MACE::inline Utility
