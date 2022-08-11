#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "argparse/argparse.hpp"

#include <optional>
#include <utility>

namespace MACE::Environment::CLI::Internal {

class CLIBase : public Utility::NonMoveableBase {
protected:
    CLIBase();
    ~CLIBase() = default;

public:
    template<typename... Args>
    argparse::Argument& AddArgument(Args&&... args);
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

} // namespace MACE::Environment::CLI::Detail

#include "MACE/Environment/CLI/internal/CLIBase.inl"
