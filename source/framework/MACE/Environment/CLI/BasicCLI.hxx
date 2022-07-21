#pragma once

#include "MACE/Environment/VerboseLevel.hxx"

#include "argparse/argparse.hpp"

namespace MACE::Environment::CLI {

class BasicCLI : public argparse::ArgumentParser {
public:
    BasicCLI();

    auto GetVerboseLevel() { return static_cast<VerboseLevel>(get<int>("-V")); }

private:
    static bool fgInstantiated;
};

} // namespace MACE::Environment::CLI
