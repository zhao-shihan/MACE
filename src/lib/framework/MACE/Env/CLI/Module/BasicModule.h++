#pragma once

#include "MACE/Env/CLI/Module/ModuleBase.h++"
#include "MACE/Env/VerboseLevel.h++"

#include <optional>
#include <type_traits>

namespace MACE::Env::CLI::inline Module {

class BasicModule : public ModuleBase {
public:
    BasicModule(argparse::ArgumentParser& argParser);

    auto VerboseLevel() const -> std::optional<enum VerboseLevel>;

private:
    std::underlying_type_t<enum VerboseLevel> fVerboseLevelValue;
};

} // namespace MACE::Env::CLI::inline Module
