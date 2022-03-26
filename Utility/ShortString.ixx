namespace MACE::Utility {

constexpr ShortString::ShortString() noexcept :
    fString{'\0'} {}

constexpr ShortString::ShortString(const ShortString& rhs) noexcept :
    ShortString(rhs.fString) {}

constexpr ShortString::ShortString(char ch) noexcept :
    fString{ch, '\0'} {}

constexpr ShortString& ShortString::operator=(const char* rhs) noexcept {
    if (rhs != fString) {
        std::strcpy(fString, rhs);
    }
    return *this;
}

constexpr ShortString& ShortString::operator=(char rhs) noexcept {
    const char temp[2] = {rhs, '\0'};
    std::strcpy(fString, temp);
    return *this;
}

constexpr ShortString& ShortString::operator+=(const char* rhs) noexcept {
    std::strcat(fString, rhs);
    return *this;
}

constexpr ShortString& ShortString::operator+=(char rhs) noexcept {
    const char temp[2] = {rhs, '\0'};
    std::strcat(fString, temp);
    return *this;
}

template<IsArithmeticButNotChar T>
constexpr ShortString& ShortString::operator+=(T rhs) noexcept {
    fgSS << fString << rhs;
    fgSS >> fString;
    fgSS.clear();
    return *this;
}

constexpr std::weak_ordering ShortString::operator<=>(const char* rhs) const noexcept {
    const auto cmpResult = std::strcmp(fString, rhs);
    if (cmpResult < 0) {
        return std::weak_ordering::less;
    } else if (cmpResult > 0) {
        return std::weak_ordering::greater;
    } else {
        return std::weak_ordering::equivalent;
    }
}

template<IsArithmeticButNotChar T>
constexpr ShortString operator+(T lhs, ShortString rhs) noexcept {
    ShortString::fgSS << lhs << rhs.fString;
    ShortString::fgSS >> rhs.fString;
    ShortString::fgSS.clear();
    return rhs;
}

} // namespace MACE::Utility
