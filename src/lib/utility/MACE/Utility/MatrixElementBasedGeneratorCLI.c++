#include "MACE/Utility/MatrixElementBasedGeneratorCLI.h++"

namespace MACE::inline Utility {

MatrixElementBasedGeneratorCLIModule::MatrixElementBasedGeneratorCLIModule(argparse::ArgumentParser& argParser) :
    ModuleBase{argParser} {
    ArgParser()
        .add_argument("-p", "--polarization")
        .help("Parent particle polarization vector")
        .required()
        .nargs(3)
        .scan<'g', double>();
    ArgParser()
        .add_argument("--normalization-factor")
        .help("Pre-computed normalization factor. Program will skip normalization and use this value if set.")
        .nargs(1)
        .scan<'g', double>();
    ArgParser()
        .add_argument("--normalization-precision-goal")
        .help("Precision goal for normalization.")
        .default_value(0.01)
        .required()
        .nargs(1)
        .scan<'g', double>();
    ArgParser()
        .add_argument("--continue-normalization")
        .help("Integration state for continuing normalization.")
        .nargs(6)
        .scan<'g', long double>();
    ArgParser()
        .add_argument("-g", "--generate")
        .help("Number of events to generate. Program will skip event generation if not set.")
        .nargs(1)
        .scan<'i', unsigned long long>();
}

auto MatrixElementBasedGeneratorCLIModule::Polarization() const -> CLHEP::Hep3Vector {
    const auto pol{ArgParser().get<std::vector<double>>("--polarization")};
    return {pol[0], pol[1], pol[2]};
}

auto MatrixElementBasedGeneratorCLIModule::ContinueNormalization() const -> std::optional<std::array<Mustard::Math::MCIntegrationState, 2>> {
    const auto cliState{ArgParser().present<std::vector<long double>>("--continue-normalization")};
    if (not cliState.has_value()) {
        return {};
    }
    std::array<Mustard::Math::MCIntegrationState, 2> state;
    state[0].sum[0] = cliState->at(0);
    state[0].sum[1] = cliState->at(1);
    state[0].n = cliState->at(2);
    state[1].sum[0] = cliState->at(3);
    state[1].sum[1] = cliState->at(4);
    state[1].n = cliState->at(5);
    return state;
}

} // namespace MACE::inline Utility
