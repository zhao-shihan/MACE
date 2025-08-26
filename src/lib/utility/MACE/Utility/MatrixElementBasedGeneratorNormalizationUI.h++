#pragma once

#include "MACE/Utility/MatrixElementBasedGeneratorCLI.h++"

#include "Mustard/CLI/CLI.h++"
#include "Mustard/Execution/Executor.h++"
#include "Mustard/IO/PrettyLog.h++"
#include "Mustard/IO/Print.h++"
#include "Mustard/Physics/Generator/MultipleTryMetropolisGenerator.h++"

#include "muc/array"

#include <algorithm>
#include <cmath>
#include <limits>

namespace MACE::inline Utility {

struct BranchingRatio {
    double value;
    double uncertainty;
};

template<int M, int N, typename A>
auto MatrixElementBasedGeneratorNormalizationUI(const Mustard::CLI::CLI<>& cli,
                                                Mustard::Executor<unsigned long long>& executor,
                                                Mustard::MultipleTryMetropolisGenerator<M, N, A>& generator,
                                                bool biased, double fullBR, double fullBRUncertainty) -> BranchingRatio;

} // namespace MACE::inline Utility

#include "MACE/Utility/MatrixElementBasedGeneratorNormalizationUI.inl"
