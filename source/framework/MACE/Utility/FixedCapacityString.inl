namespace MACE::Utility {

template<std::size_t ACapacity> // clang-format off
    requires (ACapacity >= 2)
FixedCapacityString<ACapacity>::FixedCapacityString() noexcept :
    fString{'\0'} {} // clang-format on

template<std::size_t ACapacity> // clang-format off
    requires (ACapacity >= 2)
FixedCapacityString<ACapacity>::FixedCapacityString(char ch) noexcept :
    fString{ch, '\0'} {} // clang-format on

template<std::size_t ACapacity> // clang-format off
    requires (ACapacity >= 2)
FixedCapacityString<ACapacity>::FixedCapacityString(const char* rhs) noexcept { // clang-format on
    std::strncpy(fString, rhs, max_size());
}

template<std::size_t ACapacity> // clang-format off
    requires (ACapacity >= 2)
FixedCapacityString<ACapacity>& FixedCapacityString<ACapacity>::operator=(char rhs) & noexcept { // clang-format on
    fString[0] = rhs;
    fString[1] = '\0';
    return *this;
}

template<std::size_t ACapacity> // clang-format off
    requires (ACapacity >= 2)
FixedCapacityString<ACapacity>& FixedCapacityString<ACapacity>::operator=(const char* rhs) & noexcept { // clang-format on
    if (fString != rhs) {
        if (std::ptrdiff_t diff = fString - rhs;
            diff <= -(std::ptrdiff_t)ACapacity or diff >= (std::ptrdiff_t)ACapacity) {
            std::strncpy(fString, rhs, max_size());
        } else {
            FixedCapacityString<ACapacity> rhsCopy(rhs);
            std::strncpy(fString, rhsCopy, max_size());
        }
    }
    return *this;
}

template<std::size_t ACapacity> // clang-format off
    requires (ACapacity >= 2)
FixedCapacityString<ACapacity>& FixedCapacityString<ACapacity>::operator+=(char rhs) noexcept { // clang-format on
    auto tail = fString + this->length();
    *tail = rhs;
    *++tail = '\0';
    return *this;
}

template<std::size_t ACapacity> // clang-format off
    requires (ACapacity >= 2)
FixedCapacityString<ACapacity>& FixedCapacityString<ACapacity>::operator+=(const char* rhs) noexcept { // clang-format on
    if (std::ptrdiff_t diff = fString - rhs;
        diff <= -(std::ptrdiff_t)ACapacity or diff >= (std::ptrdiff_t)ACapacity) {
        std::strncat(fString, rhs, max_size());
    } else {
        FixedCapacityString<ACapacity> rhsCopy(rhs);
        std::strncat(fString, rhsCopy, max_size());
    }
    return *this;
}

template<std::size_t ACapacity> // clang-format off
    requires (ACapacity >= 2)
std::weak_ordering FixedCapacityString<ACapacity>::operator<=>(const char* rhs) const noexcept { // clang-format on
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
