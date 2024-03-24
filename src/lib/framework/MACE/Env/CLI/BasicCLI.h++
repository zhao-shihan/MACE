#pragma once

#include "MACE/Env/CLI/CLIBase.h++"
#include "MACE/Env/VerboseLevel.h++"

#include <optional>
#include <type_traits>

namespace MACE::Env::CLI {

class BasicCLI : public CLIBase {
public:
    BasicCLI();

    auto VerboseLevel() const -> std::optional<enum VerboseLevel>;

private:
    std::underlying_type_t<enum VerboseLevel> fVerboseLevelValue;
};

} // namespace MACE::Env::CLI
