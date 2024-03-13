#include "MACE/Env/CLI/Geant4CLI.h++"

#include "CLHEP/Random/Random.h"

#include "TRandom.h"

#include <bit>
#include <random>

namespace MACE::Env::CLI {

Geant4CLI::Geant4CLI() :
    BasicCLI{} {
    AddArgument("macro")
        .help("Run the program in batch session with it. If not provided, run in interactive session with default initialization.")
        .nargs(argparse::nargs_pattern::optional);
    AddArgument("-i", "--interactive")
        .help("Run in interactive session despite of a provided macro. The macro will initialize the session.")
        .nargs(0);
    AddArgument("-s", "--seed")
        .help("Set random seed. 0 means using random device (non deterministic random seed). Predefined deterministic seed is used by default.")
        .scan<'i', long>();
}

auto Geant4CLI::SeedRandomIfFlagged() const -> bool {
    auto seed{ArgParser().present<long>("-s")};
    if (seed) {
        const auto theSeed{*seed != 0 ? *seed :
                                        std::bit_cast<int>(std::random_device{}())};
        if (const auto clhepRandom{CLHEP::HepRandom::getTheEngine()};
            clhepRandom) {
            clhepRandom->setSeed(theSeed, 3);
        }
        if (gRandom) {
            // Try to decorrelate with CLHEP
            const auto rootSeed{std::mt19937_64{static_cast<unsigned long>(theSeed)}()};
            gRandom->SetSeed(rootSeed);
        }
        return true;
    } else {
        return false;
    }
}

} // namespace MACE::Env::CLI
