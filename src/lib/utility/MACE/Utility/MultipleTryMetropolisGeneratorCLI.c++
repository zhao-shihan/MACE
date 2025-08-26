#include "MACE/Utility/MultipleTryMetropolisGeneratorCLI.h++"

namespace MACE::inline Utility {

MultipleTryMetropolisGeneratorCLIModule::MultipleTryMetropolisGeneratorCLIModule(argparse::ArgumentParser& argParser) :
    ModuleBase{argParser} {
    ArgParser()
        .add_argument("-d", "--mcmc-delta")
        .help("Step size in MCMC sampling.")
        .required()
        .nargs(1)
        .scan<'g', double>();
    ArgParser()
        .add_argument("-x", "--mcmc-discard")
        .help("Number of samples discarded between two samples generated in MCMC sampling.")
        .required()
        .nargs(1)
        .scan<'i', unsigned>();
}

} // namespace MACE::inline Utility
