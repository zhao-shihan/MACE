#pragma once

#include "MACE/Env/CLI/CLIBase.hxx"
#include "MACE/Env/VerboseLevel.hxx"

#include <optional>

namespace MACE::Env::CLI {

class BasicCLI : public CLIBase {
public:
    BasicCLI();
    virtual ~BasicCLI() = default;

    std::optional<VerboseLevel> GetVerboseLevel() const;
};

} // namespace MACE::Env::CLI
