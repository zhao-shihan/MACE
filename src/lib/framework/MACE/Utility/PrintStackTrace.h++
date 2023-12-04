#pragma once

#include <cstdio>

namespace backward {
class StackTrace;
} // namespace backward

namespace MACE::inline Utility {

void PrintStackTrace(backward::StackTrace& stack, int skip = 0, std::FILE* stream = stderr);

} // namespace MACE::inline Utility
