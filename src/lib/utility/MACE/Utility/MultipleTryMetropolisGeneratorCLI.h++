#pragma once

#include "MACE/Utility/MatrixElementBasedGeneratorCLI.h++"

#include "Mustard/CLI/CLI.h++"
#include "Mustard/CLI/Module/ModuleBase.h++"

#include <optional>

namespace MACE::inline Utility {

class MultipleTryMetropolisGeneratorCLIModule : public Mustard::CLI::ModuleBase {
public:
    MultipleTryMetropolisGeneratorCLIModule(argparse::ArgumentParser& argParser);

    auto MCMCDelta() const -> std::optional<double>;
    auto MCMCDiscard() const -> std::optional<unsigned>;
};

template<std::derived_from<Mustard::CLI::ModuleBase>... AExtraModules>
using MultipleTryMetropolisGeneratorCLI = MatrixElementBasedGeneratorCLI<MultipleTryMetropolisGeneratorCLIModule,
                                                                         AExtraModules...>;

} // namespace MACE::inline Utility
