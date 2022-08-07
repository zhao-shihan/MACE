#pragma once

#include "MACE/Environment/CLI/BasicCLI.hxx"

namespace MACE::Environment::CLI {

class Geant4CLI : public BasicCLI {
public:
    Geant4CLI();
    virtual ~Geant4CLI() = default;

    auto GetMacro() const { return GetArgParser().get("macro"); }
    auto IsInteractive() const { return GetMacro().empty() or GetArgParser().is_used("-i"); }
};

} // namespace MACE::Environment::CLI
