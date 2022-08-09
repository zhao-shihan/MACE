#pragma once

#include "MACE/Environment/detail/EnvironmentBase.hxx"
#include "MACE/Environment/Memory/FreeSingleton.hxx"
#include "MACE/Environment/VerboseLevel.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <type_traits>

namespace MACE::Environment {

namespace CLI {

class BasicCLI;

} // namespace CLI

namespace Detail {

class NoCLI {};

} // namespace Detail

using MACE::Utility::ObserverPtr;

class BasicEnvironment : public Detail::EnvironmentBase,
                         public Memory::FreeSingleton<BasicEnvironment> {
public:
    template<class ACLI = Detail::NoCLI>
    BasicEnvironment(int argc, char* argv[], ACLI&& cli, VerboseLevel verboseLevel = VerboseLevel::Warning, bool printStartupMessage = true);
    virtual ~BasicEnvironment() = default;

    const auto& GetVerboseLevel() const { return fVerboseLevel; }

protected:
    void PrintStartupMessageSplitLine() const;
    void PrintStartupMessageBody(int argc, char* argv[]) const;

private:
    VerboseLevel fVerboseLevel;
};

} // namespace MACE::Environment

#define MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out) \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(                  \
        MACE::Environment::BasicEnvironment::Instance().GetVerboseLevel(), Threshold, out)

#include "MACE/Environment/BasicEnvironment.inl"
