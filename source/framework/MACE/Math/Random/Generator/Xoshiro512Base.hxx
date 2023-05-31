#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Math/Random/Generator/XoshiroBase.hxx"
#include "MACE/Utility/InlineMacro.hxx"

#include <bit>
#include <concepts>
#include <cstdint>
#include <istream>
#include <ostream>

namespace MACE::Math::Random::inline Generator {

template<class ADerived>
class Xoshiro512Base : public XoshiroBase<ADerived, 512> {
protected:
    constexpr Xoshiro512Base();
    constexpr Xoshiro512Base(std::uint64_t seed);
    constexpr ~Xoshiro512Base() = default;

public:
    MACE_ALWAYS_INLINE constexpr void Step();

    template<Concept::Character AChar, class T>
    friend auto operator<<(std::basic_ostream<AChar>& os, const Xoshiro512Base<T>& self) -> decltype(os);
    template<Concept::Character AChar, class T>
    friend auto operator>>(std::basic_istream<AChar>& is, Xoshiro512Base<T>& self) -> decltype(is);
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/Xoshiro512Base.inl"
