#pragma once

#include "Mustard/CLI/Module/ModuleBase.h++"

#include "CLHEP/Vector/ThreeVector.h"

namespace MACE::inline Utility {

class PolarizationCLIModule : public Mustard::CLI::ModuleBase {
public:
    PolarizationCLIModule(argparse::ArgumentParser& argParser);

    auto Polarization() const -> CLHEP::Hep3Vector;
};

} // namespace MACE::inline Utility
