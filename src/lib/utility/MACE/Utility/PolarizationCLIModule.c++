#include "MACE/Utility/PolarizationCLIModule.h++"

#include <vector>

namespace MACE::inline Utility {

PolarizationCLIModule::PolarizationCLIModule(argparse::ArgumentParser& argParser) :
    ModuleBase{argParser} {
    ArgParser()
        .add_argument("-p", "--polarization")
        .help("Parent particle polarization vector")
        .required()
        .nargs(3)
        .scan<'g', double>();
}

auto PolarizationCLIModule::Polarization() const -> CLHEP::Hep3Vector {
    const auto pol{ArgParser().get<std::vector<double>>("--polarization")};
    return {pol[0], pol[1], pol[2]};
}

} // namespace MACE::inline Utility
