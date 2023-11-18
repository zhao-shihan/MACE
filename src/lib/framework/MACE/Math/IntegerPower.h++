#pragma once

#include "MACE/Concept/FundamentalType.h++"

#include <concepts>

namespace MACE::Math {

////////////////////////////////////////////////////////////////
// PowZN: {Integral} -> {Integral},
//        PowZN<N>(m)   = m^N  (partial compile-time),
//        PowZN<M, N>() = M^N  (pure compile-time).
////////////////////////////////////////////////////////////////

template<int N>
    requires(N >= 0)
constexpr auto PowZN(std::integral auto m) {
    if constexpr (N == 0) {
        return static_cast<decltype(m)>(1);
    } else if constexpr (N == 1) {
        return m;
    } else {
        if constexpr (N % 2 == 0) {
            const auto k = PowZN<N / 2>(m);
            return k * k;
        } else if constexpr (N % 3 == 0) {
            const auto k = PowZN<N / 3>(m);
            return k * k * k;
        } else {
            const auto k = PowZN<(N - 1) / 2>(m);
            return k * m * k;
        }
    }
}

////////////////////////////////////////////////////////////////
// PowRZ: {FloatingPoint} -> {FloatingPoint},
//        PowRZ<N>(x) = x^N  (partial compile-time).
////////////////////////////////////////////////////////////////

// FP version:

template<int N>
constexpr auto PowRZ(std::floating_point auto x) {
    if constexpr (N < 0) {
        return PowRZ<-N>(1 / x);
    } else if constexpr (N == 0) {
        return static_cast<decltype(x)>(1);
    } else if constexpr (N == 1) {
        return x;
    } else {
        if constexpr (N % 2 == 0) {
            const auto u = PowRZ<N / 2>(x);
            return u * u;
        } else if constexpr (N % 3 == 0) {
            const auto u = PowRZ<N / 3>(x);
            return u * u * u;
        } else {
            const auto u = PowRZ<(N - 1) / 2>(x);
            return u * x * u;
        }
    }
}

// Intergral version:

template<int N, std::floating_point F = double>
constexpr auto PowRZ(std::integral auto x) {
    return PowRZ<N>(static_cast<F>(x));
}

// Useful shorthands:

constexpr auto Pow2(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<2>(x); }
constexpr auto Pow3(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<3>(x); }
constexpr auto Pow4(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<4>(x); }
constexpr auto Pow5(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<5>(x); }
constexpr auto Pow6(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<6>(x); }
constexpr auto Pow7(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<7>(x); }
constexpr auto Pow8(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<8>(x); }
constexpr auto Pow9(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<9>(x); }
constexpr auto Pow10(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<10>(x); }
constexpr auto Pow11(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<11>(x); }
constexpr auto Pow12(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<12>(x); }
constexpr auto Pow13(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<13>(x); }
constexpr auto Pow14(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<14>(x); }
constexpr auto Pow15(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<15>(x); }
constexpr auto Pow16(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<16>(x); }
constexpr auto Pow17(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<17>(x); }
constexpr auto Pow18(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<18>(x); }
constexpr auto Pow19(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<19>(x); }
constexpr auto Pow20(Concept::Arithmetic auto x) -> decltype(auto) { return PowRZ<20>(x); }

constexpr auto Square(Concept::Arithmetic auto x) -> decltype(auto) { return Pow2(x); }
constexpr auto Cubic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow3(x); }
constexpr auto Quartic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow4(x); }
constexpr auto Quintic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow5(x); }
constexpr auto Sextic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow6(x); }
constexpr auto Septimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow7(x); }
constexpr auto Octavic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow8(x); }
constexpr auto Nonaic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow9(x); }
constexpr auto Decimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow10(x); }
constexpr auto Undecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow11(x); }
constexpr auto Duodecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow12(x); }
constexpr auto Tredecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow13(x); }
constexpr auto Quattuordecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow14(x); }
constexpr auto Quindecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow15(x); }
constexpr auto Sedecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow16(x); }
constexpr auto Septendecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow17(x); }
constexpr auto Octodecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow18(x); }
constexpr auto Novemdecimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow19(x); }
constexpr auto Vigesimic(Concept::Arithmetic auto x) -> decltype(auto) { return Pow20(x); }

} // namespace MACE::Math
