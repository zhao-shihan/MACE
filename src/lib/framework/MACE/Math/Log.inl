namespace MACE::Math {

template<std::floating_point T>
constexpr T Log(T x) noexcept {
    if constexpr (std::same_as<T, float>) {
        static_assert(std::same_as<decltype(RA3Log(x)), T>);
        return RA3Log(x);
    } else if constexpr (std::same_as<T, double>) {
        static_assert(std::same_as<decltype(RA6Log(x)), T>);
        return RA6Log(x);
    } else {
        return std::log(x);
    }
}

template<std::floating_point T>
constexpr T Log2(T x) noexcept {
    if constexpr (std::same_as<T, float>) {
        static_assert(std::same_as<decltype(RA3Log2(x)), T>);
        return RA3Log2(x);
    } else if constexpr (std::same_as<T, double>) {
        static_assert(std::same_as<decltype(RA6Log2(x)), T>);
        return RA6Log2(x);
    } else {
        return std::log2(x);
    }
}

template<std::floating_point T>
constexpr T Log10(T x) noexcept {
    if constexpr (std::same_as<T, float>) {
        static_assert(std::same_as<decltype(RA3Log10(x)), T>);
        return RA3Log10(x);
    } else if constexpr (std::same_as<T, double>) {
        static_assert(std::same_as<decltype(RA6Log10(x)), T>);
        return RA6Log10(x);
    } else {
        return std::log10(x);
    }
}

} // namespace MACE::Math
