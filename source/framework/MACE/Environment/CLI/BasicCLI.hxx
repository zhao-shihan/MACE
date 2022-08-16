#pragma once

#include "MACE/Environment/CLI/internal/CLIBase.hxx"
#include "MACE/Environment/VerboseLevel.hxx"

#include <optional>

namespace MACE::Environment::CLI {

class BasicCLI : public internal::CLIBase {
public:
    BasicCLI();
    virtual ~BasicCLI() = default;

    std::optional<VerboseLevel> GetVerboseLevel() const;
};

} // namespace MACE::Environment::CLI
