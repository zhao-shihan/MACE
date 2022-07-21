#pragma once

#include "MACE/Environment/VerboseLevel.hxx"

#include "argparse/argparse.hpp"

namespace MACE::Environment::CLI {

class BasicCLI : public argparse::ArgumentParser {
public:
    BasicCLI();

    VerboseLevel GetVerboseLevel();

private:
    static bool fgInstantiated;
};

} // namespace MACE::Environment::CLI
