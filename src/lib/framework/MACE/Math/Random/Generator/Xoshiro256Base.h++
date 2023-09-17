#pragma once

#include "MACE/Concept/FundamentalType.h++"
#include "MACE/Math/Random/Generator/XoshiroBase.h++"
#include "MACE/Utility/InlineMacro.h++"

#include <bit>
#include <concepts>
#include <cstdint>
#include <istream>
#include <ostream>

namespace MACE::Math::Random::inline Generator {

template<class ADerived>
class Xoshiro256Base : public XoshiroBase<ADerived, 256> {
protected:
    constexpr Xoshiro256Base();
    constexpr explicit Xoshiro256Base(std::uint64_t seed);
    constexpr ~Xoshiro256Base() = default;

public:
    MACE_ALWAYS_INLINE constexpr auto Step() -> void;

    template<Concept::Character AChar, class T>
    friend auto operator<<(std::basic_ostream<AChar>& os, const Xoshiro256Base<T>& self) -> decltype(os);
    template<Concept::Character AChar, class T>
    friend auto operator>>(std::basic_istream<AChar>& is, Xoshiro256Base<T>& self) -> decltype(is);
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/Xoshiro256Base.inl"
