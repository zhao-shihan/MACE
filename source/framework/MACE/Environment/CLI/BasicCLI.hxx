#pragma once

#include "argparse/argparse.hpp"

namespace MACE::Environment::CLI {

class BasicCLI : public argparse::ArgumentParser {
public:
    BasicCLI();

private:
    static bool fgInstantiate;
};

} // namespace MACE::Environment::CLI
