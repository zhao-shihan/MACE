#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Env/VerboseLevel.h++"
#include "MACE/Env/internal/EnvBase.h++"

#include "fmt/format.h"

#include <type_traits>

namespace MACE::Env {

namespace internal {

class NoCLI {};

} // namespace internal

class BasicEnv : public internal::EnvBase,
                 public Memory::PassiveSingleton<BasicEnv> {
public:
    template<typename ACLI = internal::NoCLI>
    BasicEnv(int argc, char* argv[], ACLI&& cli, VL verboseLevel = VL::Warning, bool printWelcomeMessage = true);
    virtual ~BasicEnv() = default;

    auto GetVerboseLevel() const -> const auto& { return fVerboseLevel; }

protected:
    auto PrintWelcomeMessageSplitLine() const -> void;
    auto PrintWelcomeMessageBody(int argc, char* argv[]) const -> void;

private:
    VL fVerboseLevel;
};

} // namespace MACE::Env

#define MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out) \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(                  \
        MACE::Env::BasicEnv::Instance().GetVerboseLevel(), Threshold, out)

#include "MACE/Env/BasicEnv.inl"
