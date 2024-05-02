#pragma once

#include "MACE/Env/CLI/Module/ModuleBase.h++"

namespace MACE::Env::CLI::inline Module {

class MonteCarloModule : public ModuleBase {
public:
    MonteCarloModule(argparse::ArgumentParser& argParser);

    auto SeedRandomIfFlagged() const -> bool;
};

} // namespace MACE::Env::CLI::inline Module
