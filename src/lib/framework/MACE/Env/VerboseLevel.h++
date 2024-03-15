#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"

#include <concepts>
#include <type_traits>

namespace MACE::Env {

enum struct VL {
    Quiet = -2,
    Error,
    Warning,
    Verbose,
    MoreVerbose
};

} // namespace MACE::Env

#define MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)        \
    static_assert(std::same_as<std::decay_t<decltype(verboseLevel)>,           \
                               MACE::Env::VL>);                                \
    static_assert(MACE::Env::VL::Threshold > MACE::Env::VL::Quiet,             \
                  "Threshold should at least be 'Error'");                     \
    static_assert(MACE::Concept::InstantiatedFrom<std::decay_t<decltype(out)>, \
                                                  std::basic_ostream>);        \
    if (verboseLevel >= MACE::Env::VL::Threshold) [[unlikely]]                 \
    out
