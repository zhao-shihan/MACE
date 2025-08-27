namespace MACE::inline Utility {

template<int M, int N, typename A>
auto MatrixElementBasedGeneratorCLIModule::WeightNormalization(Mustard::Executor<unsigned long long>& executor,
                                                               Mustard::MultipleTryMetropolisGenerator<M, N, A>& generator,
                                                               bool biased) const -> Mustard::Math::IntegrationResult {
    Mustard::Math::IntegrationResult factor{.value = 1, .uncertainty = 0};
    if (not biased) {
        Mustard::MasterPrintLn("Bias not set, no normalization required.");
    } else if (TheCLI()->is_used("--normalization-factor")) {
        const auto normalizationFactor{TheCLI()->get<double>("--normalization-factor")};
        factor.value = normalizationFactor;
        factor.uncertainty = std::numeric_limits<double>::quiet_NaN();
        Mustard::MasterPrintLn("Using pre-computed normalization factor {}.", normalizationFactor);
    } else {
        const auto precisionGoal{TheCLI()->get<double>("--normalization-precision-goal")};
        if (const auto integrationState{ContinueNormalization()}) {
            factor = generator.EstimateNormalizationFactor(executor, precisionGoal, *integrationState).first;
        } else {
            factor = generator.EstimateNormalizationFactor(executor, precisionGoal).first;
        }
        Mustard::MasterPrintLn("You can save the above normalization factor and integration state for future use "
                               "as long as initial state properties and bias does not change "
                               "(see option --normalization-factor and --continue-normalization).");
    }
    return factor;
}

} // namespace MACE::inline Utility
