#pragma once

#include "MACE/Utility/NonMoveableBase.h++"

#include "argparse/argparse.hpp"

namespace MACE::Env::CLI::inline Module {

class ModuleBase : public NonMoveableBase {
protected:
    ModuleBase(argparse::ArgumentParser& argParser);
    ~ModuleBase() = default;

    auto ArgParser() const -> const auto& { return *fArgParser; }
    auto ArgParser() -> auto& { return *fArgParser; }

private:
    argparse::ArgumentParser* const fArgParser;
};

} // namespace MACE::Env::CLI::inline Module
