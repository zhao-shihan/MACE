#pragma once

#include "MACE/Concept/FundamentalType.h++"
#include "MACE/Concept/InputVector.h++"
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Math/QinAlgorithm.h++"
#include "MACE/Utility/VectorCast.h++"

#include "Eigen/Core"

#include <cmath>
#include <concepts>
#include <initializer_list>
#include <ranges>
#include <stdexcept>

namespace MACE::Math {

enum struct Stat1DUse { Scalar,
                        Vector };

template<int N, Stat1DUse = Stat1DUse::Scalar>
    requires(N > 0)
class Statistic {
public:
    Statistic();
    template<std::ranges::input_range S = std::initializer_list<Eigen::Vector<double, N>>>
        requires Concept::InputVectorAny<std::ranges::range_value_t<S>, N>
    explicit Statistic(const S& sample, double weight = 1);
    template<std::ranges::input_range S = std::initializer_list<Eigen::Vector<double, N>>, std::ranges::input_range W = std::initializer_list<double>>
        requires Concept::InputVectorAny<std::ranges::range_value_t<S>, N> and std::convertible_to<std::ranges::range_value_t<W>, double>
    Statistic(const S& sample, const W& weight);

    template<Concept::InputVectorAny<N> T = Eigen::Vector<double, N>>
    auto Fill(const T& sample, double weight = 1) -> void;
    template<std::ranges::input_range S = std::initializer_list<Eigen::Vector<double, N>>>
        requires Concept::InputVectorAny<std::ranges::range_value_t<S>, N>
    auto Fill(const S& sample, double weight = 1) -> void;
    template<std::ranges::input_range S = std::initializer_list<Eigen::Vector<double, N>>, std::ranges::input_range W = std::initializer_list<double>>
        requires Concept::InputVectorAny<std::ranges::range_value_t<S>, N> and std::convertible_to<std::ranges::range_value_t<W>, double>
    auto Fill(const S& sample, const W& weight) -> void;

    auto Sum(int i) const { return fSumWX[i]; }
    auto SumProduct(int i, int j) const { return fSumWXX(i, j); }
    auto SumSquare(int i) const { return SumProduct(i, i); }
    auto SumCubic(int i) const { return fSumWX3[i]; }
    auto SumQuartic(int i) const { return fSumWX4[i]; }
    auto Sum() const -> const auto& { return fSumWX; }
    auto SumProduct() const -> const auto& { return fSumWXX; }
    auto SumSquare() const { return SumProduct().diagonal().eval(); }
    auto SumCubic() const -> const auto& { return fSumWX3; }
    auto SumQuartic() const -> const auto& { return fSumWX4; }

    auto WeightSum() const -> const auto& { return fSumW; }

    template<int K>
        requires(0 <= K and K <= 4)
    auto Moment(int i) const -> double;
    template<int K>
        requires(0 <= K and K <= 4)
    auto Moment() const -> Eigen::Vector<double, N>;

    template<int K>
        requires(0 <= K and K <= 4)
    auto CentralMoment(int i) const -> double;
    template<int K>
        requires(0 <= K and K <= 4)
    auto CentralMoment() const -> Eigen::Vector<double, N>;

    auto Mixed2ndMoment(int i, int j) const { return fSumWXX(i, j) / fSumW; }
    auto Mixed2ndMoment() const { return (fSumWXX / fSumW).eval(); }

    auto Mixed2ndCentralMoment(int i, int j) const { return Mixed2ndMoment(i, j) - Moment<1>(i) * Moment<1>(j); }
    auto Mixed2ndCentralMoment() const -> Eigen::Matrix<double, N, N>;

    auto Mean(int i) const { return Moment<1>(i); }
    auto MeanSquare(int i) { return Moment<2>(i); }
    auto MeanCubic(int i) const { return Moment<3>(i); }
    auto MeanQuartic(int i) const { return Moment<4>(i); }
    auto MeanProduct(int i, int j) const { return Mixed2ndMoment(i, j); }
    auto Mean() const { return Moment<1>(); }
    auto MeanSquare() const { return Moment<2>(); }
    auto MeanCubic() const { return Moment<3>(); }
    auto MeanQuartic() const { return Moment<4>(); }
    auto MeanProduct() const { return Mixed2ndMoment(); }

    auto Variance(int i) const { return CentralMoment<2>(i); }
    auto StdDev(int i) const { return sqrt(Variance(i)); }
    auto Covariance(int i, int j) const { return Mixed2ndCentralMoment(i, j); }
    auto Variance() const { return CentralMoment<2>(); }
    auto StdDev() const { return Variance().cwiseSqrt().eval(); }
    auto Covariance() const { return Mixed2ndCentralMoment(); }

    auto Skewness(int i) const { return CentralMoment<3>(i) / Math::Cubic(StdDev(i)); }
    auto Skewness() const -> Eigen::Vector<double, N>;

    auto Kurtosis(int i) const { return CentralMoment<4>(i) / Math::Square(Variance(i)); }
    auto Kurtosis() const -> Eigen::Vector<double, N>;

protected:
    Eigen::Vector<double, N> fSumWX;
    Eigen::Matrix<double, N, N> fSumWXX;
    Eigen::Vector<double, N> fSumWX3;
    Eigen::Vector<double, N> fSumWX4;
    double fSumW;
};

template<>
class Statistic<1, Stat1DUse::Scalar> : protected Statistic<1, Stat1DUse::Vector> {
private:
    using Base = Statistic<1, Stat1DUse::Vector>;

public:
    Statistic();
    template<std::ranges::input_range S = std::initializer_list<double>>
        requires std::convertible_to<std::ranges::range_value_t<S>, double>
    explicit Statistic(const S& sample, double weight = 1);
    template<std::ranges::input_range S = std::initializer_list<double>, std::ranges::input_range W = std::initializer_list<double>>
        requires std::convertible_to<std::ranges::range_value_t<S>, double> and std::convertible_to<std::ranges::range_value_t<W>, double>
    Statistic(const S& sample, const W& weight);

    auto Fill(double sample, double weight = 1) -> void { Base::Fill({sample}, weight); }
    template<std::ranges::input_range S = std::initializer_list<double>>
        requires std::convertible_to<std::ranges::range_value_t<S>, double>
    auto Fill(const S& sample, double weight = 1) -> void;
    template<std::ranges::input_range S = std::initializer_list<double>, std::ranges::input_range W = std::initializer_list<double>>
        requires std::convertible_to<std::ranges::range_value_t<S>, double> and std::convertible_to<std::ranges::range_value_t<W>, double>
    auto Fill(const S& sample, const W& weight) -> void;

    auto Sum() const { return Sum(0); }
    auto SumSquare() const { return SumSquare(0); }
    auto SumCubic() const { return SumCubic(0); }
    auto SumQuartic() const { return SumQuartic(0); }

    auto WeightSum() const -> const auto& { return fSumW; }

    template<int K>
    auto Moment() const { return Moment<K>(0); }
    template<int K>
    auto CentralMoment() const { return CentralMoment<K>(0); }

    auto Mean() const { return Moment<1>(); }
    auto MeanSquare() { return Moment<2>(); }
    auto MeanCubic() const { return Moment<3>(); }
    auto MeanQuartic() const { return Moment<4>(); }

    auto Variance() const { return CentralMoment<2>(); }
    auto StdDev() const { return sqrt(Variance()); }

    auto Skewness() const { return CentralMoment<3>() / Math::Cubic(StdDev()); }

    auto Kurtosis() const { return CentralMoment<4>() / Math::Square(Variance()); }
};

} // namespace MACE::Math

#include "MACE/Math/Statistic.inl"
