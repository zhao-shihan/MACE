#pragma once

#include <istream>
#include <ostream>

namespace MACE::Concept {

template<typename T>
concept StreamInputable = requires(std::istream& is, T& obj) {
    { is >> obj } -> std::same_as<std::ostream&>;
};

template<typename T>
concept StreamOutputable = requires(std::ostream& os, const T& obj) {
    { os << obj } -> std::same_as<std::ostream&>;
};

template<typename T>
concept StreamIOable = StreamInputable<T> and StreamOutputable<T>;

} // namespace MACE::Concept
