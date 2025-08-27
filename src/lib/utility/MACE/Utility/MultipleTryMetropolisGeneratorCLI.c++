#include "MACE/Utility/MultipleTryMetropolisGeneratorCLI.h++"

#include "Mustard/CLI/CLI.h++"
#include "Mustard/IO/PrettyLog.h++"

#include "fmt/core.h"

#include <cstdlib>

namespace MACE::inline Utility {

MultipleTryMetropolisGeneratorCLIModule::MultipleTryMetropolisGeneratorCLIModule(gsl::not_null<Mustard::CLI::CLI<>*> cli) :
    ModuleBase{cli} {
    TheCLI()
        ->add_argument("-d", "--mcmc-delta")
        .help("Step size in MCMC sampling. [required if --generate set]")
        .nargs(1)
        .scan<'g', double>();
    TheCLI()
        ->add_argument("-x", "--mcmc-discard")
        .help("Number of samples discarded between two samples generated in MCMC sampling. [required if --generate set]")
        .nargs(1)
        .scan<'i', unsigned>();
}

auto MultipleTryMetropolisGeneratorCLIModule::MCMCDelta() const -> std::optional<double> {
    const auto delta{TheCLI()->present<double>("--mcmc-delta")};
    if (delta) {
        return delta;
    }
    if (TheCLI()->is_used("--generate")) {
        const auto [_, argv]{TheCLI().ArgcArgv()};
        Mustard::MasterPrintError(fmt::format("Option -g or --generate passed but -d or --mcmc-delta not set. Try {} --help", argv[0]));
        std::exit(EXIT_FAILURE);
    }
    return delta;
}

auto MultipleTryMetropolisGeneratorCLIModule::MCMCDiscard() const -> std::optional<unsigned> {
    const auto discard{TheCLI()->present<unsigned>("--mcmc-discard")};
    if (discard) {
        return discard;
    }
    if (TheCLI()->is_used("--generate")) {
        const auto [_, argv]{TheCLI().ArgcArgv()};
        Mustard::MasterPrintError(fmt::format("Option -g or --generate passed but -x or --mcmc-discard not set. Try {} --help", argv[0]));
        std::exit(EXIT_FAILURE);
    }
    return discard;
}

} // namespace MACE::inline Utility
