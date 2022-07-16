#pragma once

#include <type_traits>

namespace MACE::Utility {

enum class VerboseLevel : int {
    Quiet = -1,
    Error,
    Warning,
    Verbose,
    MoreVerbose,
    Undefined = 0xABCDEF
};

#define MACE_VERBOSE_LEVEL_CONTROLLED_OUT(ostream, Threshold, verboseLevel)                   \
    static_assert(std::is_same_v<std::remove_cvref_t<decltype(verboseLevel)>, VerboseLevel>); \
    if (verboseLevel >= MACE::Utility::VerboseLevel::Threshold) ostream

} // namespace MACE::Utility
