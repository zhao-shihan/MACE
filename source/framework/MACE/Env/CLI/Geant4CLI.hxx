#pragma once

#include "MACE/Env/CLI/BasicCLI.hxx"

namespace MACE::Env::CLI {

class Geant4CLI : public BasicCLI {
public:
    Geant4CLI();
    virtual ~Geant4CLI() = default;

    auto GetMacro() const { return GetArgParser().get("macro"); }
    auto IsInteractive() const { return GetMacro().empty() or GetArgParser().is_used("-i"); }
};

} // namespace MACE::Env::CLI
