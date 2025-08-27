#pragma once

#include "MACE/Utility/EventGeneratorCLI.h++"

#include "Mustard/CLI/CLI.h++"
#include "Mustard/CLI/Module/ModuleBase.h++"
#include "Mustard/Execution/Executor.h++"
#include "Mustard/IO/PrettyLog.h++"
#include "Mustard/IO/Print.h++"
#include "Mustard/Math/IntegrationResult.h++"
#include "Mustard/Math/MCIntegrationState.h++"
#include "Mustard/Physics/Generator/MultipleTryMetropolisGenerator.h++"

#include "muc/array"

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <optional>

namespace MACE::inline Utility {

class MatrixElementBasedGeneratorCLIModule : public Mustard::CLI::ModuleBase {
public:
    MatrixElementBasedGeneratorCLIModule(gsl::not_null<Mustard::CLI::CLI<>*> cli);

    template<int M, int N, typename A>
    auto WeightNormalization(Mustard::Executor<unsigned long long>& executor,
                       Mustard::MultipleTryMetropolisGenerator<M, N, A>& generator,
                       bool biased) const -> Mustard::Math::IntegrationResult;

private:
    auto ContinueNormalization() const -> std::optional<std::array<Mustard::Math::MCIntegrationState, 2>>;
};

template<std::derived_from<Mustard::CLI::ModuleBase>... AExtraModules>
using MatrixElementBasedGeneratorCLI = EventGeneratorCLI<MatrixElementBasedGeneratorCLIModule,
                                                         AExtraModules...>;

} // namespace MACE::inline Utility

#include "MACE/Utility/MatrixElementBasedGeneratorCLI.inl"
