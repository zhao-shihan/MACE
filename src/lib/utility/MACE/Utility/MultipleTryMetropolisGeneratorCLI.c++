#include "MACE/Utility/MultipleTryMetropolisGeneratorCLI.h++"

#include "Mustard/IO/PrettyLog.h++"

#include <cstdlib>

namespace MACE::inline Utility {

MultipleTryMetropolisGeneratorCLIModule::MultipleTryMetropolisGeneratorCLIModule(argparse::ArgumentParser& argParser) :
    ModuleBase{argParser} {
    ArgParser()
        .add_argument("-d", "--mcmc-delta")
        .help("Step size in MCMC sampling. [required if --generate set]")
        .nargs(1)
        .scan<'g', double>();
    ArgParser()
        .add_argument("-x", "--mcmc-discard")
        .help("Number of samples discarded between two samples generated in MCMC sampling. [required if --generate set]")
        .nargs(1)
        .scan<'i', unsigned>();
}

auto MultipleTryMetropolisGeneratorCLIModule::MCMCDelta() const -> std::optional<double> {
    const auto delta{ArgParser().present<double>("--mcmc-delta")};
    if (delta) {
        return delta;
    }
    if (ArgParser().is_used("--generate")) {
        Mustard::MasterPrintError("Option --generate passed but --mcmc-delta not set. Try --help");
        std::exit(EXIT_FAILURE);
    }
    return delta;
}

auto MultipleTryMetropolisGeneratorCLIModule::MCMCDiscard() const -> std::optional<unsigned> {
    const auto discard{ArgParser().present<unsigned>("--mcmc-discard")};
    if (discard) {
        return discard;
    }
    if (ArgParser().is_used("--generate")) {
        Mustard::MasterPrintError("Option --generate passed but --mcmc-discard not set. Try --help");
        std::exit(EXIT_FAILURE);
    }
    return discard;
}

} // namespace MACE::inline Utility
