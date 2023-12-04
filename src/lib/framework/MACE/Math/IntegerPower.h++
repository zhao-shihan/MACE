#pragma once

#include "MACE/Concept/FundamentalType.h++"

#include <concepts>

namespace MACE::Math {

////////////////////////////////////////////////////////////////
// IPow: {Integral} -> {Integral},
//        IPow<N>(m)   = m^N  (partial compile-time),
////////////////////////////////////////////////////////////////

template<int N>
    requires(N >= 0)
constexpr auto IPow(std::integral auto m) -> auto {
    if constexpr (N == 0) {
        return static_cast<decltype(m)>(1);
    } else if constexpr (N == 1) {
        return m;
    } else {
        if constexpr (N % 2 == 0) {
            const auto k = IPow<N / 2>(m);
            return k * k;
        } else if constexpr (N % 3 == 0) {
            const auto k = IPow<N / 3>(m);
            return k * k * k;
        } else {
            const auto k = IPow<(N - 1) / 2>(m);
            return k * m * k;
        }
    }
}

////////////////////////////////////////////////////////////////
// Pow: {FloatingPoint} -> {FloatingPoint},
//        Pow<N>(x) = x^N  (partial compile-time).
////////////////////////////////////////////////////////////////

// FP version:

template<int N>
constexpr auto Pow(std::floating_point auto x) -> auto {
    if constexpr (N < 0) {
        return Pow<-N>(1 / x);
    } else if constexpr (N == 0) {
        return static_cast<decltype(x)>(1);
    } else if constexpr (N == 1) {
        return x;
    } else {
        if constexpr (N % 2 == 0) {
            const auto u = Pow<N / 2>(x);
            return u * u;
        } else if constexpr (N % 3 == 0) {
            const auto u = Pow<N / 3>(x);
            return u * u * u;
        } else {
            const auto u = Pow<(N - 1) / 2>(x);
            return u * x * u;
        }
    }
}

// Intergral version:

template<int N, std::floating_point F = double>
constexpr auto Pow(std::integral auto x) -> auto {
    return Pow<N>(static_cast<F>(x));
}

// constexpr auto Square(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<2>(x); }
// constexpr auto Cubic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<3>(x); }
// constexpr auto Quartic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<4>(x); }
// constexpr auto Quintic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<5>(x); }
// constexpr auto Sextic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<6>(x); }
// constexpr auto Septimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<7>(x); }
// constexpr auto Octavic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<8>(x); }
// constexpr auto Nonaic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<9>(x); }
// constexpr auto Decimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<10>(x); }
// constexpr auto Undecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<11>(x); }
// constexpr auto Duodecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<12>(x); }
// constexpr auto Tredecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<13>(x); }
// constexpr auto Quattuordecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<14>(x); }
// constexpr auto Quindecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<15>(x); }
// constexpr auto Sedecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<16>(x); }
// constexpr auto Septendecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<17>(x); }
// constexpr auto Octodecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<18>(x); }
// constexpr auto Novemdecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<19>(x); }
// constexpr auto Vigesimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow<20>(x); }

} // namespace MACE::Math
