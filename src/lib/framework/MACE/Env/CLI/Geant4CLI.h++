#pragma once

#include "MACE/Env/CLI/MonteCarloCLI.h++"

namespace MACE::Env::CLI {

class Geant4CLI : public MonteCarloCLI {
public:
    Geant4CLI();

    auto Macro() const -> auto { return ArgParser().present("macro"); }
    auto IsInteractive() const -> auto { return not Macro().has_value() or ArgParser().is_used("-i"); }
};

} // namespace MACE::Env::CLI
