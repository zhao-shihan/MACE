#pragma once

#include "MACE/Env/CLI/CLIBase.h++"
#include "MACE/Env/VerboseLevel.h++"

#include <optional>

namespace MACE::Env::CLI {

class BasicCLI : public CLIBase {
public:
    BasicCLI();
    virtual ~BasicCLI() = default;

    auto VerboseLevel() const -> std::optional<VL>;

private:
    int fVerboseLevelValue;
};

} // namespace MACE::Env::CLI
