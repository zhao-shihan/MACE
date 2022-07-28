#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "argparse/argparse.hpp"

#include <memory>
#include <optional>

namespace MACE::Environment::CLI::Detail {

class CLIBase : private Utility::NonMoveableBase {
protected:
    CLIBase();
    ~CLIBase() = default;

public:
    void ParseArgs(int argc, char* argv[]);
    auto Parsed() const { return fArguments.has_value(); }
    int GetArgc() const;
    char** GetArgv() const;
    const auto& GetArgParser() const { return *fArgParser; }

protected:
    std::unique_ptr<argparse::ArgumentParser> fArgParser;

private:
    std::optional<std::pair<int, char**>> fArguments;
};

} // namespace MACE::Environment::CLI::Detail
