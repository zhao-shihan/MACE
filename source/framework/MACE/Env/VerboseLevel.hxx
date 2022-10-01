#pragma once

#include <concepts>
#include <type_traits>

namespace MACE::Env {

enum class VerboseLevel {
    Quiet = -2,
    Error,
    Warning,
    Verbose,
    MoreVerbose,
    Undefined = 0xABCDEF
};

} // namespace MACE::Env

#define MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)                \
    static_assert(std::same_as<std::remove_cvref_t<decltype(verboseLevel)>,            \
                               MACE::Env::VerboseLevel>);                              \
    static_assert(MACE::Env::VerboseLevel::Threshold > MACE::Env::VerboseLevel::Quiet, \
                  "Threshold should at least be 'Error'");                             \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>,                \
                                    std::ostream>);                                    \
    if (verboseLevel >= MACE::Env::VerboseLevel::Threshold) [[unlikely]]               \
    out
