#pragma once

#include "MACE/Env/CLI/BasicCLI.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Env/VerboseLevel.h++"
#include "MACE/Env/internal/EnvBase.h++"

#include <optional>
#include <functional>

namespace MACE::Env {

class BasicEnv : public internal::EnvBase,
                 public Memory::PassiveSingleton<BasicEnv> {
public:
    BasicEnv(int argc, char* argv[], std::optional<std::reference_wrapper<CLI::BasicCLI>> cli = {}, VL verboseLevel = {}, bool printWelcomeMessage = true);
    virtual ~BasicEnv() = default;

    auto Argc() const -> auto { return fArgc; }
    auto Argv() const -> auto { return fArgv; }
    auto VerboseLevel() const -> const auto& { return fVerboseLevel; }

protected:
    auto PrintWelcomeMessageSplitLine() const -> void;
    auto PrintWelcomeMessageBody(int argc, char* argv[]) const -> void;

private:
    int fArgc;
    char** fArgv;
    VL fVerboseLevel;
};

} // namespace MACE::Env

#define MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out) \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(                  \
        MACE::Env::BasicEnv::Instance().VerboseLevel(), Threshold, out)
