#pragma once

#include "MACE/Env/CLI/BasicCLI.h++"

namespace MACE::Env::CLI {

class MonteCarloCLI : public BasicCLI {
public:
    MonteCarloCLI();

    auto SeedRandomIfFlagged() const -> bool;
};

} // namespace MACE::Env::CLI
