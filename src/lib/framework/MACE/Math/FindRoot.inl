namespace MACE::Math::FindRoot {

template<std::floating_point T>
auto NewtonRaphson(const std::regular_invocable<T> auto& f,
                   const std::regular_invocable<T> auto& df,
                   T x0,
                   int maxIterations,
                   T tolerance) -> std::pair<T, bool> {
    auto x1{x0 - f(x0) / df(x0)};
    for (int i{}; i < maxIterations; ++i) {
        if (std23::isnan(x1)) {
            break;
        }
        if (std23::abs(x1 - x0) <= std23::abs(Math::MidPoint(x1, x0)) * tolerance) {
            return {x1, true};
        }
        x0 = x1;
        x1 = x0 - f(x0) / df(x0);
    }
    return {x1, false};
}

template<std::floating_point T>
auto Secant(const std::regular_invocable<T> auto& f,
            T x0,
            std::optional<T> x1O,
            int maxIterations,
            T tolerance) -> std::pair<T, bool> {
    auto fx0{f(x0)};
    if (fx0 == 0) {
        return {x0, true};
    }
    auto x1{x1O.value_or(x0 + fx0 * 2 * tolerance / (f(x0 - tolerance) - f(x0 + tolerance)))};
    auto fx1{f(x1)};
    auto x2{(x0 * fx1 - x1 * fx0) / (fx1 - fx0)};
    for (int i{}; i < maxIterations; ++i) {
        if (std23::isnan(x2)) {
            break;
        }
        if (std23::abs(x2 - x1) <= std23::abs(Math::MidPoint(x2, x1)) * tolerance) {
            return {x2, true};
        }
        x0 = x1;
        fx0 = fx1;
        x1 = x2;
        fx1 = f(x2);
        x2 = (x0 * fx1 - x1 * fx0) / (fx1 - fx0);
    }
    return {x2, false};
}

} // namespace MACE::Math::FindRoot
