#pragma once

#include "MACE/Utility/NonMoveableBase.h++"

#include "argparse/argparse.hpp"

#include <optional>
#include <utility>

namespace MACE::Env::CLI {

class CLIBase : public NonMoveableBase {
public:
    CLIBase();
    virtual ~CLIBase() = 0;

private:
    struct ArgcArgvType {
        int argc;
        char** argv;
    };

public:
    auto AddArgument(auto&&... args) -> argparse::Argument&;
    auto AddMutuallyExclusiveGroup(bool required = false) -> argparse::ArgumentParser::MutuallyExclusiveGroup&;
    auto ParseArgs(int argc, char* argv[]) -> void;
    auto Parsed() const -> bool { return fArgcArgv.has_value(); }
    auto ArgParser() const -> const auto& { return fArgParser; }
    auto ArgcArgv() const -> ArgcArgvType;

protected:
    [[noreturn]] static auto ThrowParsed() -> void;
    [[noreturn]] static auto ThrowNotParsed() -> void;

private:
    std::optional<ArgcArgvType> fArgcArgv;
    argparse::ArgumentParser fArgParser;
};

} // namespace MACE::Env::CLI

#include "MACE/Env/CLI/CLIBase.inl"
