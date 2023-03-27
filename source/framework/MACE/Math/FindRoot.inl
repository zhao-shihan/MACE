namespace MACE::Math {

template<std::floating_point T>
constexpr std::pair<T, bool> FindRoot(const std::regular_invocable<T> auto& F,
                                      const std::regular_invocable<T> auto& DF,
                                      T x0,
                                      const T tolerance,
                                      const int maxIterations) {
    auto converged = false;
    auto x1 = x0 - F(x0) / DF(x0);
    for (auto i = 0; i < maxIterations; ++i) {
        if (std2b::abs(x1 - x0) <= std2b::abs(x0) * tolerance) {
            converged = true;
            break;
        }
        x0 = x1;
        x1 = x0 - F(x0) / DF(x0);
    }
    return {x1, converged};
}

template<std::floating_point T>
constexpr std::pair<T, bool> FindRoot(const std::regular_invocable<T> auto& F,
                                      T x0,
                                      const T tolerance,
                                      const int maxIterations) {
    auto converged = false;
    auto x1 = x0 - F(x0) * 2 * tolerance / (F(x0 + tolerance) - F(x0 - tolerance));
    auto x2 = x1 - F(x1) * (x1 - x0) / (F(x1) - F(x0));
    for (auto i = 0; i < maxIterations; ++i) {
        if (std2b::abs(x1 - x0) <= std2b::abs(x0) * tolerance) {
            converged = true;
            break;
        }
        x0 = x1;
        x1 = x2;
        x2 = x1 - F(x1) * (x1 - x0) / (F(x1) - F(x0));
    }
    return {x2, converged};
}

} // namespace MACE::Math
