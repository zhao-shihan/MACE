#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "argparse/argparse.hpp"

#include <optional>
#include <utility>

namespace MACE::Env::CLI {

class CLIBase : public Utility::NonMoveableBase {
protected:
    CLIBase();
    ~CLIBase() = default;

public:
    argparse::Argument& AddArgument(auto&&... args);
    void ParseArgs(int argc, char* argv[]);
    auto Parsed() const { return fArguments.has_value(); }
    const auto& GetArgParser() const { return fArgParser; }
    const std::pair<int, char**>& GetArgcArgv() const;

protected:
    [[noreturn]] static void ThrowParsed();
    [[noreturn]] static void ThrowNotParsed();

private:
    std::optional<std::pair<int, char**>> fArguments;
    argparse::ArgumentParser fArgParser;
};

} // namespace MACE::Env::CLI

#include "MACE/Env/CLI/CLIBase.inl"
