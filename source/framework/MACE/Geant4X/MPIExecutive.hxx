#pragma once

#include "MACE/Env/BasicEnv.hxx"
#include "MACE/Env/CLI/Geant4CLI.hxx"
#include "MACE/Env/Memory/MuteSingleton.hxx"
#include "MACE/Utility/TupleForEach.hxx"

#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

namespace MACE::Geant4X {

using Env::CLI::Geant4CLI;

class MPIExecutive final : public Env::Memory::MuteSingleton<MPIExecutive> {
public:
    MPIExecutive() = default;

    void StartSession(const Geant4CLI& cli, auto&& macOrCMDs = {}) const;
    void StartInteractiveSession(int argc, char* argv[], auto&& macOrCMDs = {}) const;
    void StartBatchSession(auto&& macOrCMDs) const { Execute(std::forward<decltype(macOrCMDs)>(macOrCMDs)); }

private:
    void CheckSequential() const;

    static bool ExecuteCommand(const std::string& command);

    static void Execute(const std::string& macro);
    static void Execute(const std::ranges::range auto& cmdText) requires
        std::convertible_to<typename std::remove_cvref_t<decltype(cmdText)>::value_type, std::string>;
};

} // namespace MACE::Geant4X

#include "MACE/Geant4X/MPIExecutive.inl"
