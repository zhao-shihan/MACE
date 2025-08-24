namespace MACE::GeneratorAppUtility {

template<int M, int N, typename A>
auto MTMGeneratorNormalizationUI(Mustard::Env::CLI::CLI<>& cli,
                                 Mustard::Executor<unsigned long long>& executor,
                                 Mustard::MultipleTryMetropolisGenerator<M, N, A>& generator,
                                 bool biased, double fullBR, double fullBRUncertainty) -> std::optional<double> {
    const auto nEvent{cli->get<unsigned long long>("n-event")};
    double branchingRatio;
    double branchingRatioUncertainty;
    if (not biased) {
        branchingRatio = fullBR;
        branchingRatioUncertainty = fullBRUncertainty;
        Mustard::MasterPrintLn("No bias has been set.");
    } else if (cli->is_used("--normalization-factor")) {
        const auto normalizationFactor{cli->get<double>("--normalization-factor")};
        branchingRatio = normalizationFactor * fullBR;
        branchingRatioUncertainty = std::numeric_limits<double>::quiet_NaN();
        Mustard::MasterPrintLn("Using pre-computed normalization factor {}.", normalizationFactor);
    } else {
        const auto nSample{cli->is_used("--n-normalization") ?
                               cli->get<unsigned long long>("--n-normalization") :
                               nEvent * (cli->get<unsigned>("--mcmc-discard") + 1)};
        const auto factor{generator.EstimateNormalizationFactor(nSample, executor)};
        executor.PrintExecutionSummary();
        if (not generator.CheckNormalizationFactor(factor)) {
            Mustard::MasterPrintWarning("Use option -n or --n-normalization to independently set number of samples used in normalization");
            return {};
        }
        branchingRatio = factor.value * fullBR;
        branchingRatioUncertainty = std::hypot(factor.uncertainty * fullBR, fullBRUncertainty);
        Mustard::MasterPrintLn("You can save the normalization factor for future use "
                               "as long as bias does not change (see option -f or --normalization-factor).");
    }
    Mustard::MasterPrintLn("Branching ratio = {} +/- {}", branchingRatio, branchingRatioUncertainty);
    const auto weightScale{branchingRatio / nEvent};
    return weightScale;
}

} // namespace MACE::GeneratorAppUtility
