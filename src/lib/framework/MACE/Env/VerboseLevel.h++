#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"

#include <concepts>
#include <type_traits>

namespace MACE::Env {

enum struct VerboseLevel {
    Quiet = -2,
    Error,
    Warning,
    Informative,
    Verbose
};

} // namespace MACE::Env

#define MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)        \
    static_assert(std::same_as<std::decay_t<decltype(verboseLevel)>,           \
                               MACE::Env::VerboseLevel>);                                \
    static_assert(MACE::Env::VerboseLevel::Threshold > MACE::Env::VerboseLevel::Quiet,             \
                  "Threshold should at least be 'Error'");                     \
    static_assert(MACE::Concept::InstantiatedFrom<std::decay_t<decltype(out)>, \
                                                  std::basic_ostream>);        \
    if (verboseLevel >= MACE::Env::VerboseLevel::Threshold) [[unlikely]]                 \
    out
