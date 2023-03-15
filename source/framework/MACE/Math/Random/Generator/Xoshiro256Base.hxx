#pragma once

#include "MACE/Math/Random/UniformPseudoRandomBitGeneratorBase.hxx"

#include <bit>
#include <concepts>
#include <cstdint>
#include <limits>
#include <random>
#include <type_traits>

namespace MACE::Math::Random::Generator {

template<class ADerived>
class Xoshiro256Base : public UniformPseudoRandomBitGeneratorBase<ADerived, std::uint64_t> {
public:
    constexpr Xoshiro256Base();
    constexpr Xoshiro256Base(std::uint64_t seed);

protected:
    constexpr ~Xoshiro256Base() = default;

public:
    constexpr void Step();
    constexpr void Seed(std::uint64_t seed);

    static constexpr auto Min() { return std::numeric_limits<std::uint64_t>::min(); }
    static constexpr auto Max() { return std::numeric_limits<std::uint64_t>::max(); }

    template<Concept::Character AChar, class T>
        requires std::derived_from<T, Xoshiro256Base<T>>
    friend auto operator<<(std::basic_ostream<AChar>& os, const T& self) -> decltype(os);
    template<Concept::Character AChar, class T>
        requires std::derived_from<T, Xoshiro256Base<T>>
    friend auto operator>>(std::basic_istream<AChar>& is, T& self) -> decltype(is);

protected:
    std::uint64_t fState[4];
};

} // namespace MACE::Math::Random::Generator

#include "MACE/Math/Random/Generator/Xoshiro256Base.inl"
