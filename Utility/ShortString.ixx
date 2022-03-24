namespace MACE::Utility {

inline constexpr ShortString::ShortString() noexcept :
    fString{'\0'} {}

inline constexpr ShortString::ShortString(const ShortString& rhs) noexcept :
    ShortString(rhs.fString) {}

inline constexpr ShortString::ShortString(char ch) noexcept :
    fString{ch, '\0'} {}

inline constexpr ShortString& ShortString::operator=(const char* rhs) noexcept {
    if (rhs != fString) {
        std::strcpy(fString, rhs);
    }
    return *this;
}

inline constexpr ShortString& ShortString::operator=(char rhs) noexcept {
    const char temp[2] = {rhs, '\0'};
    std::strcpy(fString, temp);
    return *this;
}

inline constexpr ShortString& ShortString::operator+=(const char* rhs) noexcept {
    std::strcat(fString, rhs);
    return *this;
}

inline constexpr ShortString& ShortString::operator+=(char rhs) noexcept {
    const char temp[2] = {rhs, '\0'};
    std::strcat(fString, temp);
    return *this;
}

inline constexpr std::weak_ordering ShortString::operator<=>(const char* rhs) const noexcept {
    const auto cmpResult = std::strcmp(fString, rhs);
    if (cmpResult < 0) {
        return std::weak_ordering::less;
    } else if (cmpResult > 0) {
        return std::weak_ordering::greater;
    } else {
        return std::weak_ordering::equivalent;
    }
}

} // namespace MACE::Utility
