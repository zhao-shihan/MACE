#pragma once

#include "Mustard/Env/CLI/CLI.h++"
#include "Mustard/Execution/Executor.h++"
#include "Mustard/IO/PrettyLog.h++"
#include "Mustard/IO/Print.h++"
#include "Mustard/Physics/Generator/MultipleTryMetropolisGenerator.h++"

#include "muc/array"

#include <algorithm>
#include <cmath>
#include <limits>

namespace MACE::GeneratorAppUtility {

struct BranchingRatio {
    double value;
    double uncertainty;
};

template<int M, int N, typename A>
auto MatrixElementBasedGeneratorNormalizationUI(Mustard::Env::CLI::CLI<>& cli,
                                                Mustard::Executor<unsigned long long>& executor,
                                                Mustard::MultipleTryMetropolisGenerator<M, N, A>& generator,
                                                bool biased, double fullBR, double fullBRUncertainty) -> BranchingRatio;

} // namespace MACE::GeneratorAppUtility

#include "MACE/GeneratorAppUtility/MatrixElementBasedGeneratorNormalizationUI.inl"
