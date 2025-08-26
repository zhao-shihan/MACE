namespace MACE::GeneratorAppUtility {

template<int M, int N, typename A>
auto MatrixElementBasedGeneratorNormalizationUI(Mustard::CLI::CLI<>& cli,
                                                Mustard::Executor<unsigned long long>& executor,
                                                Mustard::MultipleTryMetropolisGenerator<M, N, A>& generator,
                                                bool biased, double fullBR, double fullBRUncertainty) -> BranchingRatio {
    BranchingRatio bR;
    if (not biased) {
        bR.value = fullBR;
        bR.uncertainty = fullBRUncertainty;
        Mustard::MasterPrintLn("No bias has been set.");
    } else if (cli->is_used("--normalization-factor")) {
        const auto normalizationFactor{cli->get<double>("--normalization-factor")};
        bR.value = normalizationFactor * fullBR;
        bR.uncertainty = std::numeric_limits<double>::quiet_NaN();
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
        bR.value = factor.value * fullBR;
        bR.uncertainty = std::hypot(fullBR * factor.uncertainty, factor.value * fullBRUncertainty);
        Mustard::MasterPrintLn("You can save the above normalization factor and integration state for future use as long as "
                               "bias does not change (see option --normalization-factor and --continue-normalization).");
    }
    Mustard::MasterPrintLn("Branching ratio:\n"
                           "  {} +/- {}  (rel. unc.: {:.2}%)",
                           bR.value, bR.uncertainty, bR.uncertainty / bR.value * 100);
    return bR;
}

} // namespace MACE::GeneratorAppUtility
