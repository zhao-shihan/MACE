#pragma once

#include "Mustard/Env/CLI/CLI.h++"
#include "Mustard/Execution/Executor.h++"
#include "Mustard/IO/PrettyLog.h++"
#include "Mustard/IO/Print.h++"
#include "Mustard/Physics/Generator/MultipleTryMetropolisGenerator.h++"

#include <cmath>
#include <limits>
#include <optional>

namespace MACE::GeneratorAppUtility {

template<int M, int N, typename A>
auto MTMGeneratorNormalizationUI(Mustard::Env::CLI::CLI<>& cli,
                                 Mustard::Executor<unsigned long long>& executor,
                                 Mustard::MultipleTryMetropolisGenerator<M, N, A>& generator,
                                 bool biased, double fullBR, double fullBRUncertainty) -> std::optional<double>;

} // namespace MACE::GeneratorAppUtility

#include "MACE/GeneratorAppUtility/MTMGeneratorNormalizationUI.inl"
