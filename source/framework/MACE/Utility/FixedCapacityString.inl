namespace MACE::Utility {

template<size_t CapacityV> // clang-format off
    requires (CapacityV >= 2)
FixedCapacityString<CapacityV>::FixedCapacityString() noexcept :
    fString{'\0'} {} // clang-format on

template<size_t CapacityV> // clang-format off
    requires (CapacityV >= 2)
FixedCapacityString<CapacityV>::FixedCapacityString(char ch) noexcept :
    fString{ch, '\0'} {} // clang-format on

template<size_t CapacityV> // clang-format off
    requires (CapacityV >= 2)
FixedCapacityString<CapacityV>::FixedCapacityString(const char* rhs) noexcept { // clang-format on
    std::strncpy(fString, rhs, max_size());
}

template<size_t CapacityV> // clang-format off
    requires (CapacityV >= 2)
FixedCapacityString<CapacityV>& FixedCapacityString<CapacityV>::operator=(char rhs) & noexcept { // clang-format on
    fString[0] = rhs;
    fString[1] = '\0';
    return *this;
}

template<size_t CapacityV> // clang-format off
    requires (CapacityV >= 2)
FixedCapacityString<CapacityV>& FixedCapacityString<CapacityV>::operator=(const char* rhs) & noexcept { // clang-format on
    if (fString != rhs) {
        if (std::ptrdiff_t diff = fString - rhs;
            diff <= -(std::ptrdiff_t)CapacityV or diff >= (std::ptrdiff_t)CapacityV) {
            std::strncpy(fString, rhs, max_size());
        } else {
            FixedCapacityString<CapacityV> rhsCopy(rhs);
            std::strncpy(fString, rhsCopy, max_size());
        }
    }
    return *this;
}

template<size_t CapacityV> // clang-format off
    requires (CapacityV >= 2)
FixedCapacityString<CapacityV>& FixedCapacityString<CapacityV>::operator+=(char rhs) noexcept { // clang-format on
    auto tail = fString + this->length();
    *tail = rhs;
    *++tail = '\0';
    return *this;
}

template<size_t CapacityV> // clang-format off
    requires (CapacityV >= 2)
FixedCapacityString<CapacityV>& FixedCapacityString<CapacityV>::operator+=(const char* rhs) noexcept { // clang-format on
    if (std::ptrdiff_t diff = fString - rhs;
        diff <= -(std::ptrdiff_t)CapacityV or diff >= (std::ptrdiff_t)CapacityV) {
        std::strncat(fString, rhs, max_size());
    } else {
        FixedCapacityString<CapacityV> rhsCopy(rhs);
        std::strncat(fString, rhsCopy, max_size());
    }
    return *this;
}

template<size_t CapacityV> // clang-format off
    requires (CapacityV >= 2)
std::weak_ordering FixedCapacityString<CapacityV>::operator<=>(const char* rhs) const noexcept { // clang-format on
    const auto cmpResult = std::strncmp(fString, rhs, max_size());
    if (cmpResult < 0) {
        return std::weak_ordering::less;
    } else if (cmpResult > 0) {
        return std::weak_ordering::greater;
    } else {
        return std::weak_ordering::equivalent;
    }
}

} // namespace MACE::Utility
