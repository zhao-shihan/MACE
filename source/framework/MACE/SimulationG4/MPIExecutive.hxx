#pragma once

#include "MACE/Environment/BasicEnvironment.hxx"
#include "MACE/Environment/Memory/FreeSingleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include <iostream>
#include <ranges>
#include <string>

namespace MACE::SimulationG4 {

using Utility::ObserverPtr;

class MPIExecutive final : public Environment::Memory::FreeSingleton<MPIExecutive> {
public:
    MPIExecutive();

    void StartInteractiveSession(int argc, char* argv[], const char* macro = "") const { StartInteractiveSession(argc, argv, std::string(macro)); }
    void StartInteractiveSession(int argc, char* argv[], const std::ranges::range auto& macroOrCommands) const;
    void StartBatchSession(const char* macro) const { StartBatchSession(std::string(macro)); }
    void StartBatchSession(const std::ranges::range auto& macroOrCommands) const { Execute(macroOrCommands); }

private:
    void Execute(const std::convertible_to<std::string> auto& macro) const { fG4UIManager->ExecuteMacroFile(std::string(macro).c_str()); }
    template<std::ranges::range ARange> // clang-format off
        requires std::convertible_to<typename ARange::value_type, std::string>
    void Execute(const ARange& commandList) const; // clang-format on

    void CheckSequential() const;

private:
    const ObserverPtr<G4UImanager> fG4UIManager;
};

} // namespace MACE::SimulationG4

#include "MACE/SimulationG4/MPIExecutive.inl"
