#pragma once

#include <cstdio>

#include "MACE/Utility/InlineMacro.h++"

namespace MACE::inline Utility {

MACE_NOINLINE auto PrintStackTrace(int depth = 64, int skip = 0, std::FILE* stream = stderr) -> void;

} // namespace MACE::inline Utility
