#pragma once

#include "MACE/Environment/detail/SignalHandler.hxx"
#include "MACE/Environment/Resource/detail/SingletonFactory.hxx"
#include "MACE/Environment/VerboseLevel.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <functional>
#include <optional>

namespace MACE::Environment {

namespace CLI {

class BasicCLI;

} // namespace CLI

using MACE::Utility::ObserverPtr;

class BasicEnvironment {
public:
    BasicEnvironment(int argc, char* argv[], std::optional<std::reference_wrapper<CLI::BasicCLI>> optCLI,
                     VerboseLevel verboseLevel = VerboseLevel::Warning, bool printStartupMessage = true);
    virtual ~BasicEnvironment();
    BasicEnvironment(const BasicEnvironment&) = delete;
    BasicEnvironment& operator=(const BasicEnvironment&) = delete;

    static auto Initialized() { return fgBasicEnvironmentInstance != nullptr; }
    static auto Finalized() { return fgBasicEnvironmentFinalized; }
    static auto Available() { return Initialized() and not Finalized(); }
    static auto& Instance() { return *fgBasicEnvironmentInstance; }

    const auto& GetVerboseLevel() const { return fVerboseLevel; }

protected:
    void PrintStartupMessageSplitLine() const;
    void PrintStartupMessageBody(int argc, char* argv[]) const;

private:
    Detail::SignalHandler fSignalHandler;
    VerboseLevel fVerboseLevel;
    Memory::Detail::SingletonFactory fSingletonFactory;

    static ObserverPtr<BasicEnvironment> fgBasicEnvironmentInstance;
    static bool fgBasicEnvironmentFinalized;
};

} // namespace MACE::Environment
