#pragma once

#include "MACE/Env/CLI/BasicCLI.h++"

namespace MACE::Env::CLI {

class Geant4CLI : public BasicCLI {
public:
    Geant4CLI();
    virtual ~Geant4CLI() = default;

    auto Macro() const -> auto { return ArgParser().get("macro"); }
    auto IsInteractive() const -> auto { return Macro().empty() or ArgParser().is_used("-i"); }
};

} // namespace MACE::Env::CLI
