#pragma once

#include "MACE/Env/internal/EnvBase.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Env/VerboseLevel.h++"

#include <type_traits>

namespace MACE::Env {

namespace internal {

class NoCLI {};

} // namespace internal

class BasicEnv : public internal::EnvBase,
                 public Memory::PassiveSingleton<BasicEnv> {
public:
    template<typename ACLI = internal::NoCLI>
    BasicEnv(int argc, char* argv[], ACLI&& cli, VerboseLevel verboseLevel = VerboseLevel::Warning, bool printWelcomeMessage = true);
    virtual ~BasicEnv() = default;

    const auto& GetVerboseLevel() const { return fVerboseLevel; }

protected:
    void PrintWelcomeMessageSplitLine() const;
    void PrintWelcomeMessageBody(int argc, char* argv[]) const;

private:
    VerboseLevel fVerboseLevel;
};

} // namespace MACE::Env

#define MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out) \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(                  \
        MACE::Env::BasicEnv::Instance().GetVerboseLevel(), Threshold, out)

#include "MACE/Env/BasicEnv.inl"
