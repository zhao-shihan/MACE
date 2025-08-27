#pragma once

#include "Mustard/CLI/CLI.h++"
#include "Mustard/CLI/Module/ModuleBase.h++"
#include "Mustard/CLI/MonteCarloCLI.h++"
#include "Mustard/Math/MCIntegrationState.h++"

#include <array>
#include <optional>

namespace MACE::inline Utility {

class MatrixElementBasedGeneratorCLIModule : public Mustard::CLI::ModuleBase {
public:
    MatrixElementBasedGeneratorCLIModule(argparse::ArgumentParser& argParser);

    auto ContinueNormalization() const -> std::optional<std::array<Mustard::Math::MCIntegrationState, 2>>;
};

template<std::derived_from<Mustard::CLI::ModuleBase>... AExtraModules>
using MatrixElementBasedGeneratorCLI = Mustard::CLI::MonteCarloCLI<MatrixElementBasedGeneratorCLIModule,
                                                                   AExtraModules...>;

} // namespace MACE::inline Utility
