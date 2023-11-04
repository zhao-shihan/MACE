namespace MACE::Math {

template<int N, Stat1DUse U>
    requires(N > 0)
Statistic<N, U>::Statistic() :
    fSumWX{},
    fSumWXX{},
    fSumWX3{},
    fSumWX4{},
    fSumW{} {}

template<int N, Stat1DUse U>
    requires(N > 0)
template<std::ranges::input_range S>
    requires Concept::InputVectorAny<std::ranges::range_value_t<S>, N>
Statistic<N, U>::Statistic(const S& sample, double weight) :
    Statistic{} {
    Fill(sample, weight);
}

template<int N, Stat1DUse U>
    requires(N > 0)
template<std::ranges::input_range S, std::ranges::input_range W>
    requires Concept::InputVectorAny<std::ranges::range_value_t<S>, N> and std::convertible_to<std::ranges::range_value_t<W>, double>
Statistic<N, U>::Statistic(const S& sample, const W& weight) :
    Statistic{} {
    Fill(sample, weight);
}

template<int N, Stat1DUse U>
    requires(N > 0)
template<Concept::InputVectorAny<N> T>
auto Statistic<N, U>::Fill(const T& sample, double weight) -> void {
    const auto x{VectorCast<Eigen::Vector<double, N>>(sample)};
    auto wx{weight * x};
    fSumWX += wx;
    fSumWXX += wx * x.transpose();
    wx = wx.cwiseProduct(x).cwiseProduct(x);
    fSumWX3 += wx;
    wx = wx.cwiseProduct(x);
    fSumWX4 += wx;
    fSumW += weight;
}

template<int N, Stat1DUse U>
    requires(N > 0)
template<std::ranges::input_range S>
    requires Concept::InputVectorAny<std::ranges::range_value_t<S>, N>
auto Statistic<N, U>::Fill(const S& sample, double weight) -> void {
    for (auto&& s : sample) {
        Fill(s, weight);
    }
}

template<int N, Stat1DUse U>
    requires(N > 0)
template<std::ranges::input_range S, std::ranges::input_range W>
    requires Concept::InputVectorAny<std::ranges::range_value_t<S>, N> and std::convertible_to<std::ranges::range_value_t<W>, double>
auto Statistic<N, U>::Fill(const S& sample, const W& weight) -> void {
    if (std::ranges::size(sample) > std::ranges::size(weight)) {
        throw std::invalid_argument{"MACE::Math::Statistic::Fill: size of sample > size of weight"};
    }
    auto s = std::ranges::begin(sample);
    auto w = std::ranges::begin(weight);
    const auto sEnd = std::ranges::end(sample);
    while (s != sEnd) {
        Fill(*s++, *w++);
    }
}

template<int N, Stat1DUse U>
    requires(N > 0)
template<int K>
    requires(0 <= K and K <= 4)
auto Statistic<N, U>::Moment(int i) const -> double {
    if constexpr (K == 0) { return 1; }
    if constexpr (K == 1) { return fSumWX[i] / fSumW; }
    if constexpr (K == 2) { return fSumWXX(i, i) / fSumW; }
    if constexpr (K == 3) { return fSumWX3[i] / fSumW; }
    if constexpr (K == 4) { return fSumWX4[i] / fSumW; }
}

template<int N, Stat1DUse U>
    requires(N > 0)
template<int K>
    requires(0 <= K and K <= 4)
auto Statistic<N, U>::Moment() const -> Eigen::Vector<double, N> {
    if constexpr (K == 0) { return Eigen::Vector<double, N>::Constant(1); }
    if constexpr (K == 1) { return fSumWX / fSumW; }
    if constexpr (K == 2) { return fSumWXX.diagonal() / fSumW; }
    if constexpr (K == 3) { return fSumWX3 / fSumW; }
    if constexpr (K == 4) { return fSumWX4 / fSumW; }
}

template<int N, Stat1DUse U>
    requires(N > 0)
template<int K>
    requires(0 <= K and K <= 4)
auto Statistic<N, U>::CentralMoment(int i) const -> double {
    if constexpr (K == 0) { return 1; }
    if constexpr (K == 1) { return 0; }
    if constexpr (K == 2) { return Moment<2>(i) - Math::Square(Moment<1>(i)); }
    if constexpr (K == 3) { return Math::QinPolynomial({Moment<3>(i), -3 * Moment<2>(i), 0, 2}, Moment<1>(i)); }
    if constexpr (K == 4) { return Math::QinPolynomial({Moment<4>(i), -4 * Moment<3>(i), 6 * Moment<2>(i), 0, -3}, Moment<1>(i)); }
}

template<int N, Stat1DUse U>
    requires(N > 0)
template<int K>
    requires(0 <= K and K <= 4)
auto Statistic<N, U>::CentralMoment() const -> Eigen::Vector<double, N> {
    if constexpr (K == 0) {
        return Eigen::Vector<double, N>::Constant(1);
    }
    if constexpr (K == 1) {
        return Eigen::Vector<double, N>::Zeros();
    }
    if constexpr (K == 2) {
        const auto m1 = Moment<1>();
        return Moment<2>() - m1.cwiseProduct(m1);
    }
    if constexpr (K == 3) {
        const auto m1 = Moment<1>();
        return Moment<3>() + m1.cwiseProduct(-3 * Moment<2>() + 2 * m1.cwiseProduct(m1));
    }
    if constexpr (K == 4) {
        const auto m1 = Moment<1>();
        return Moment<4>() + m1.cwiseProduct(-4 * Moment<3>() + m1.cwiseProduct(6 * Moment<2>() - 3 * m1.cwiseProduct(m1)));
    }
}

template<int N, Stat1DUse U>
    requires(N > 0)
auto Statistic<N, U>::Mixed2ndCentralMoment() const -> Eigen::Matrix<double, N, N> {
    const auto m1 = Moment<1>();
    return Mixed2ndMoment() - m1 * m1.transpose();
}

template<int N, Stat1DUse U>
    requires(N > 0)
auto Statistic<N, U>::Skewness() const -> Eigen::Vector<double, N> {
    const auto stdDev = StdDev();
    return CentralMoment<3>() / stdDev.cwiseProduct(stdDev).cwiseProduct(stdDev);
}

template<int N, Stat1DUse U>
    requires(N > 0)
auto Statistic<N, U>::Kurtosis() const -> Eigen::Vector<double, N> {
    const auto variance = Variance();
    return CentralMoment<4>() / variance.cwiseProduct(variance);
}

template<>
Statistic<1, Stat1DUse::Scalar>::Statistic() :
    Base{} {}

template<>
template<std::ranges::input_range S>
    requires std::convertible_to<std::ranges::range_value_t<S>, double>
Statistic<1, Stat1DUse::Scalar>::Statistic(const S& sample, double weight) :
    Statistic{} {
    Fill(sample, weight);
}

template<>
template<std::ranges::input_range S, std::ranges::input_range W>
    requires std::convertible_to<std::ranges::range_value_t<S>, double> and std::convertible_to<std::ranges::range_value_t<W>, double>
Statistic<1, Stat1DUse::Scalar>::Statistic(const S& sample, const W& weight) :
    Statistic{} {
    Fill(sample, weight);
}

template<>
template<std::ranges::input_range S>
    requires std::convertible_to<std::ranges::range_value_t<S>, double>
auto Statistic<1, Stat1DUse::Scalar>::Fill(const S& sample, double weight) -> void {
    for (auto&& s : sample) {
        Fill(s, weight);
    }
}

template<std::ranges::input_range S, std::ranges::input_range W>
    requires std::convertible_to<std::ranges::range_value_t<S>, double> and std::convertible_to<std::ranges::range_value_t<W>, double>
auto Statistic<1, Stat1DUse::Scalar>::Fill(const S& sample, const W& weight) -> void {
    if (std::ranges::size(sample) > std::ranges::size(weight)) {
        throw std::invalid_argument{"MACE::Math::Statistic::Fill: size of sample > size of weight"};
    }
    auto s = std::ranges::begin(sample);
    auto w = std::ranges::begin(weight);
    const auto sEnd = std::ranges::end(sample);
    while (s != sEnd) {
        Fill(*s++, *w++);
    }
}

} // namespace MACE::Math
