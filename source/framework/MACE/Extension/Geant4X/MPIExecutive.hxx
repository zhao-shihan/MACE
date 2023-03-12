#pragma once

#include "MACE/Env/BasicEnv.hxx"
#include "MACE/Env/CLI/Geant4CLI.hxx"
#include "MACE/Env/Memory/MuteSingleton.hxx"

#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

namespace MACE::inline Extension::Geant4X {

using Env::CLI::Geant4CLI;

class MPIExecutive final : public Env::Memory::MuteSingleton<MPIExecutive> {
public:
    void StartSession(const Geant4CLI& cli, auto&& macFileOrCmdList) const;
    template<typename T>
    void StartSession(const Geant4CLI& cli, std::initializer_list<T> cmdList = {}) const;

    void StartSession(int argc, char* argv[], auto&& macFileOrCmdList) const;
    template<typename T>
    void StartSession(int argc, char* argv[], std::initializer_list<T> cmdList = {}) const;

    void StartInteractiveSession(int argc, char* argv[], auto&& macFileOrCmdList) const;
    template<typename T>
    void StartInteractiveSession(int argc, char* argv[], std::initializer_list<T> cmdList = {}) const;

    void StartBatchSession(auto&& macFileOrCmdList) const;
    template<typename T>
    void StartBatchSession(std::initializer_list<T> cmdList) const;

private:
    void StartSessionImpl(const Geant4CLI& cli, auto&& macFileOrCmdList) const;
    void StartSessionImpl(int argc, char* argv[], auto&& macFileOrCmdList) const;
    void StartInteractiveSessionImpl(int argc, char* argv[], auto&& macFileOrCmdList) const;
    void StartBatchSessionImpl(auto&& macFileOrCmdList) const;

    void CheckSequential() const;

    static bool ExecuteCommand(const std::string& command);

    static void Execute(const std::string& macro);
    static void Execute(const std::ranges::input_range auto& cmdList)
        requires std::convertible_to<typename std::remove_cvref_t<decltype(cmdList)>::value_type, std::string>;
};

} // namespace MACE::inline Extension::Geant4X

#include "MACE/Extension/Geant4X/MPIExecutive.inl"
