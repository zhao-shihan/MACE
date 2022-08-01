#pragma once

#include "MACE/Environment/CLI/detail/CLIBase.hxx"
#include "MACE/Environment/VerboseLevel.hxx"

#include <optional>

namespace MACE::Environment::CLI {

class BasicCLI : public Detail::CLIBase {
public:
    BasicCLI();
    virtual ~BasicCLI() = default;

    std::optional<VerboseLevel> GetVerboseLevel() const;
};

} // namespace MACE::Environment::CLI
