#pragma once

#include "MACE/Environment/detail/EnvironmentBase.hxx"
#include "MACE/Environment/Memory/FreeSingleton.hxx"
#include "MACE/Environment/VerboseLevel.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <functional>
#include <optional>

namespace MACE::Environment {

namespace CLI {

class BasicCLI;

} // namespace CLI

using MACE::Utility::ObserverPtr;

class BasicEnvironment : public Detail::EnvironmentBase,
                         public Memory::FreeSingleton<BasicEnvironment> {
public:
    BasicEnvironment(int argc, char* argv[], std::optional<std::reference_wrapper<CLI::BasicCLI>> optCLI,
                     VerboseLevel verboseLevel = VerboseLevel::Warning, bool printStartupMessage = true);
    virtual ~BasicEnvironment() = default;

    const auto& GetVerboseLevel() const { return fVerboseLevel; }

protected:
    void PrintStartupMessageSplitLine() const;
    void PrintStartupMessageBody(int argc, char* argv[]) const;

private:
    VerboseLevel fVerboseLevel;
};

} // namespace MACE::Environment
