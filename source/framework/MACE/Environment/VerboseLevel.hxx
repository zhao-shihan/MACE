#pragma once

namespace MACE::Environment {

enum class VerboseLevel {
    Quiet = -1,
    Error,
    Warning,
    Verbose,
    MoreVerbose,
    Undefined = 0xABCDEF
};

#define MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, ostream)   \
    static_assert(std::is_same_v<std::remove_cvref_t<decltype(verboseLevel)>, \
                                 MACE::Environment::VerboseLevel>);           \
    if (verboseLevel >= MACE::Environment::VerboseLevel::Threshold) ostream

} // namespace MACE::Environment
