#pragma once

#include "MACE/Env/CLI/Module/ModuleBase.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "argparse/argparse.hpp"

#include <concepts>
#include <memory>
#include <optional>
#include <utility>

namespace MACE::Env::CLI {

template<std::derived_from<ModuleBase>... AModules>
class CLI;

template<>
class CLI<> : public NonMoveableBase {
public:
    CLI();
    virtual ~CLI() = 0;

private:
    struct ArgcArgvType {
        int argc;
        char** argv;
    };

public:
    auto ParseArgs(int argc, char* argv[]) -> void;
    auto Parsed() const -> bool { return fArgcArgv.has_value(); }
    auto ArgcArgv() const -> ArgcArgvType;

protected:
    auto ArgParser() const -> const auto& { return *fArgParser; }
    auto ArgParser() -> auto& { return *fArgParser; }

protected:
    [[noreturn]] static auto ThrowParsed() -> void;
    [[noreturn]] static auto ThrowNotParsed() -> void;

private:
    std::optional<ArgcArgvType> fArgcArgv;
    std::unique_ptr<argparse::ArgumentParser> fArgParser;
};

template<std::derived_from<ModuleBase>... AModules>
class CLI : public CLI<>,
            public AModules... {
public:
    CLI();
};

} // namespace MACE::Env::CLI

#include "MACE/Env/CLI/CLI.inl"
