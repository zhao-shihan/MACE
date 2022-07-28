#pragma once

#include "MACE/Environment/CLI/BasicCLI.hxx"

namespace MACE::Environment::CLI {

class SimulationG4CLI : public BasicCLI {
public:
    SimulationG4CLI();
    virtual ~SimulationG4CLI() = default;

    auto GetMacro() const { return fArgParser->get("macro"); }
    auto IsInteractive() const { return GetMacro().empty() or fArgParser->is_used("-i"); }
};

} // namespace MACE::Environment::CLI
