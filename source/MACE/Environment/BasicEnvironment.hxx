#pragma once

#include "MACE/Environment/Resource/SingletonFactory.hxx"
#include "MACE/Utility/ObserverPtr.hxx"
#include "MACE/Utility/VerboseLevel.hxx"

#include <memory>

namespace MACE::Environment {

using MACE::Utility::ObserverPtr;
using Utility::VerboseLevel;

class BasicEnvironment {
public:
    BasicEnvironment(int argc, char* argv[], VerboseLevel verboseLevel = VerboseLevel::Undefined, bool printStartupMessage = true);
    virtual ~BasicEnvironment() { fgBasicEnvironmentFinalized = true; }
    BasicEnvironment(const BasicEnvironment&) = delete;
    BasicEnvironment& operator=(const BasicEnvironment&) = delete;

    static auto Initialized() { return fgBasicEnvironmentInstance != nullptr; }
    static auto Finalized() { return fgBasicEnvironmentFinalized; }
    static auto Available() { return Initialized() and not Finalized(); }
    static auto& Instance() { return *fgBasicEnvironmentInstance; }

    const auto& GetVerboseLevel() const { return fVerboseLevel; }
    Resource::SingletonFactory& GetSingletonFactory();

protected:
    void PrintStartupMessageSplitLine() const;
    void PrintStartupMessageBody(int argc, char* argv[]) const;

private:
    VerboseLevel fVerboseLevel;
    std::unique_ptr<Resource::SingletonFactory> fSingletonFactory;

    static ObserverPtr<BasicEnvironment> fgBasicEnvironmentInstance;
    static bool fgBasicEnvironmentFinalized;
};

} // namespace MACE::Environment
