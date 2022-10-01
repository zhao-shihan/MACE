#pragma once

#include "MACE/Env/internal/EnvBase.hxx"
#include "MACE/Env/Memory/FreeSingleton.hxx"
#include "MACE/Env/VerboseLevel.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <type_traits>

namespace MACE::Env {

namespace CLI {

class BasicCLI;

} // namespace CLI

namespace internal {

class NoCLI {};

} // namespace internal

using MACE::Utility::ObserverPtr;

class BasicEnv : public internal::EnvBase,
                         public Memory::FreeSingleton<BasicEnv> {
public:
    template<class ACLI = internal::NoCLI>
    BasicEnv(int argc, char* argv[], ACLI&& cli, VerboseLevel verboseLevel = VerboseLevel::Warning, bool printStartupMessage = true);
    virtual ~BasicEnv() = default;

    const auto& GetVerboseLevel() const { return fVerboseLevel; }

protected:
    void PrintStartupMessageSplitLine() const;
    void PrintStartupMessageBody(int argc, char* argv[]) const;

private:
    VerboseLevel fVerboseLevel;
};

} // namespace MACE::Env

#define MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out) \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(                  \
        MACE::Env::BasicEnv::Instance().GetVerboseLevel(), Threshold, out)

#include "MACE/Env/BasicEnv.inl"
