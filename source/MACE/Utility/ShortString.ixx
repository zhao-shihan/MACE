namespace MACE::Utility {

template<typename T>
ShortString& ShortString::operator+=(T rhs) noexcept requires(std::is_arithmetic_v<T> and not std::same_as<T, char>) {
    fgSS.clear();
    fgSS << fString << rhs;
    fgSS >> fString;
    return *this;
}

template<typename T>
ShortString operator+(T lhs, ShortString rhs) noexcept requires(std::is_arithmetic_v<T> and not std::same_as<T, char>) {
    ShortString::fgSS.clear();
    ShortString::fgSS << lhs << rhs.fString;
    ShortString::fgSS >> rhs.fString;
    return rhs;
}

} // namespace MACE::Utility
