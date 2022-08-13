#pragma once

#include <istream>
#include <ostream>

namespace MACE::Utility::Concept {

template<typename T>
concept StreamInputable = requires(const std::istream& in, const T& obj) {
    in >> obj;
};

template<typename T>
concept StreamOutputable = requires(const std::ostream& out, const T& obj) {
    out << obj;
};

template<typename T>
concept StreamIOable = StreamInputable<T> and StreamOutputable<T>;

} // namespace MACE::Utility::Concept
