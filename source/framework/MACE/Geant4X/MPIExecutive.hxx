#pragma once

#include "MACE/Environment/BasicEnvironment.hxx"
#include "MACE/Environment/CLI/SimulationG4CLI.hxx"
#include "MACE/Environment/Memory/MuteSingleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"
#include "MACE/Utility/TupleForEach.hxx"

#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>

namespace MACE::Geant4X {

namespace Envirionment::CLI {

class SimulationG4CLI;

} // namespace Envirionment::CLI

using Environment::CLI::SimulationG4CLI;
using Utility::ObserverPtr;

class MPIExecutive final : public Environment::Memory::MuteSingleton<MPIExecutive> {
public:
    MPIExecutive() = default;

    template<class AMacroOrCommand>
    void StartSession(const SimulationG4CLI& cli, AMacroOrCommand&& macroOrCommands = std::string()) const;
    template<class AMacroOrCommand>
    void StartInteractiveSession(int argc, char* argv[], AMacroOrCommand&& macroOrCommands = std::string()) const;
    template<class AMacroOrCommand>
    void StartBatchSession(AMacroOrCommand&& macroOrCommands) const { Execute(std::forward<AMacroOrCommand>(macroOrCommands)); }

private:
    void CheckSequential() const;

    static void Execute(const std::string& macro);
    template<std::ranges::range ARange> // clang-format off
        requires std::convertible_to<typename ARange::value_type, std::string>
    static void Execute(const ARange& commandList) ; // clang-format on
    template<std::convertible_to<std::string>... AStrings>
    static void Execute(const std::tuple<AStrings...>& commandList);

    static bool ExecuteCommand(const std::string& command);
};

} // namespace MACE::SimulationG4

#include "MACE/Geant4X/MPIExecutive.inl"
