#pragma once

#include "MACE/Environment/VerboseLevel.hxx"
#include "MACE/Utility/NonCopyableBase.hxx"

#include "argparse/argparse.hpp"

namespace MACE::Environment::CLI {

class BasicCLI : public Utility::NonCopyableBase {
public:
    BasicCLI();

    const auto& GetArgParser() const { return fArgParser; }
    void ParseArgs(int argc, const char* const argv[]);

    auto GetVerboseLevel() { return static_cast<VerboseLevel>(fArgParser.get<int>("-V")); }

protected:
    argparse::ArgumentParser fArgParser;
};

} // namespace MACE::Environment::CLI
