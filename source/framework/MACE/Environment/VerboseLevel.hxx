#pragma once

#include <concepts>
#include <type_traits>

namespace MACE::Environment {

enum class VerboseLevel {
    Quiet = -2,
    Error,
    Warning,
    Verbose,
    MoreVerbose,
    Undefined = 0xABCDEF
};

} // namespace MACE::Environment

#define MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)                                \
    static_assert(std::same_as<std::remove_cvref_t<decltype(verboseLevel)>,                            \
                               MACE::Environment::VerboseLevel>);                                      \
    static_assert(MACE::Environment::VerboseLevel::Threshold > MACE::Environment::VerboseLevel::Quiet, \
                  "Threshold should at least be 'Error'");                                             \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>,                                \
                                    std::ostream>);                                                    \
    if (verboseLevel >= MACE::Environment::VerboseLevel::Threshold) [[unlikely]]                       \
    out
