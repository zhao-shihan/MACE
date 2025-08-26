namespace MACE::GeneratorAppUtility {

template<int M, int N, typename A>
auto MTMGeneratorNormalizationUI(Mustard::Env::CLI::CLI<>& cli,
                                 Mustard::Executor<unsigned long long>& executor,
                                 Mustard::MultipleTryMetropolisGenerator<M, N, A>& generator,
                                 bool biased, double fullBR, double fullBRUncertainty) -> double {
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
        struct Mustard::MultipleTryMetropolisGenerator<M, N, A>::IntegrationResult factor;
        const auto precisionGoal{cli->get<double>("--normalization-precision-goal")};
        if (cli->is_used("--continue-normalization")) {
            std::array<struct Mustard::MultipleTryMetropolisGenerator<M, N, A>::IntegrationState, 2> integrationState;
            const auto inputIntegrationState{cli->get<std::vector<long double>>("--continue-normalization")};
            integrationState[0].sum[0] = inputIntegrationState[0];
            integrationState[0].sum[1] = inputIntegrationState[1];
            integrationState[0].n = inputIntegrationState[2];
            integrationState[1].sum[0] = inputIntegrationState[3];
            integrationState[1].sum[1] = inputIntegrationState[4];
            integrationState[1].n = inputIntegrationState[5];
            factor = generator.EstimateNormalizationFactor(executor, precisionGoal, integrationState).first;
        } else {
            factor = generator.EstimateNormalizationFactor(executor, precisionGoal).first;
        }
        branchingRatio = factor.value * fullBR;
        branchingRatioUncertainty = std::hypot(fullBR * factor.uncertainty, factor.value * fullBRUncertainty);
        Mustard::MasterPrintLn("You can save the normalization factor and integration state for future use "
                               "as long as bias does not change (see option -f or --normalization-factor, "
                               "and option --continue-normalization).");
    }
    Mustard::MasterPrintLn("Branching ratio = {} +/- {}", branchingRatio, branchingRatioUncertainty);
    const auto weightScale{branchingRatio / nEvent};
    return weightScale;
}

} // namespace MACE::GeneratorAppUtility
