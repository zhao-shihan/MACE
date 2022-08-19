namespace MACE::Utility {

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
FixedString<AMaxSize>::FixedString() noexcept :
    fString{'\0'} {} // clang-format on

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
FixedString<AMaxSize>::FixedString(char ch) noexcept :
    fString{ch, '\0'} {} // clang-format on

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
FixedString<AMaxSize>::FixedString(FixedString<AMaxSize>::ConstPointer str) noexcept :
    fString{} { // clang-format on
    std::strncpy(fString, str, AMaxSize);
}

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
FixedString<AMaxSize>::FixedString(const std::derived_from<std::string> auto& str) noexcept :
    fString{} { // clang-format on
    const auto len = str.std::string::length();
    std::memcpy(fString, str.std::string::c_str(), len);
    fString[len] = '\0';
}

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
FixedString<AMaxSize>::FixedString(const auto& str) noexcept // clang-format on
    requires(std::convertible_to<decltype(str), std::string_view> and not std::convertible_to<decltype(str), ConstPointer>) :
    fString{} {
    const std::string_view view = str;
    const auto len = view.length();
    std::memcpy(fString, view.data(), len);
    fString[len] = '\0';
}

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
FixedString<AMaxSize>& FixedString<AMaxSize>::operator=(char ch) & noexcept { // clang-format on
    fString[0] = ch;
    fString[1] = '\0';
    return *this;
}

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
FixedString<AMaxSize>& FixedString<AMaxSize>::operator=(FixedString<AMaxSize>::ConstPointer rhs) & noexcept { // clang-format on
    if (fString != rhs) {
        if (std::cmp_greater_equal(std::distance(CBegin(), rhs), Capacity())) {
            std::strncpy(fString, rhs, AMaxSize);
        } else {
            const FixedString<AMaxSize> rhsCopy = rhs;
            std::strncpy(fString, rhsCopy.fString, AMaxSize);
        }
    }
    return *this;
}

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
FixedString<AMaxSize>& FixedString<AMaxSize>::operator=(const std::derived_from<std::string> auto& rhs) & noexcept { // clang-format on
    const auto len = rhs.std::string::length();
    std::memcpy(fString, rhs.std::string::c_str(), len);
    fString[len] = '\0';
    return *this;
}

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
FixedString<AMaxSize>& FixedString<AMaxSize>::operator=(const auto& rhs) & noexcept // clang-format on
    requires(std::convertible_to<decltype(rhs), std::string_view> and not std::convertible_to<decltype(rhs), ConstPointer>) {
    const std::string_view view = rhs;
    const auto len = view.length();
    std::memmove(fString, view.data(), len);
    fString[len] = '\0';
    return *this;
}

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
FixedString<AMaxSize>& FixedString<AMaxSize>::Append(char ch) noexcept { // clang-format on
    auto tail = End();
    *tail = ch;
    *++tail = '\0';
    return *this;
}

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
FixedString<AMaxSize>& FixedString<AMaxSize>::Append(FixedString<AMaxSize>::ConstPointer str) noexcept { // clang-format on
    if (std::cmp_greater_equal(std::distance(CBegin(), str), Capacity())) {
        std::strncat(fString, str, AMaxSize);
    } else {
        const FixedString<AMaxSize> strCopy = str;
        std::strncat(fString, strCopy.fString, AMaxSize);
    }
    return *this;
}

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
FixedString<AMaxSize>& FixedString<AMaxSize>::Append(const std::derived_from<std::string> auto& str) noexcept { // clang-format on
    const auto tail = End();
    const auto count = str.std::string::length();
    std::memcpy(tail, str.std::string::c_str(), count);
    *(tail + count) = '\0';
    return *this;
}

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
FixedString<AMaxSize>& FixedString<AMaxSize>::Append(const auto& str) noexcept // clang-format on
    requires(std::convertible_to<decltype(str), std::string_view> and not std::convertible_to<decltype(str), ConstPointer>) {
    const std::string_view view = str;
    const auto tail = End();
    const auto count = view.length();
    std::memmove(tail, view.data(), count);
    *(tail + count) = '\0';
    return *this;
}

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
bool FixedString<AMaxSize>::operator==(const auto& rhs) const noexcept // clang-format on
    requires(std::convertible_to<decltype(rhs), std::string_view> and not std::convertible_to<decltype(rhs), ConstPointer>) {
    const std::string_view view = rhs;
    const auto len = view.length();
    if (Length() != len) { return false; }
    return std::memcmp(fString, view.data(), len) == 0;
}

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
std::strong_ordering FixedString<AMaxSize>::operator<=>(FixedString<AMaxSize>::ConstPointer rhs) const noexcept { // clang-format on
    const auto cmp = std::strncmp(fString, rhs, AMaxSize);
    return cmp == 0 ? std::strong_ordering::equal :
           cmp < 0  ? std::strong_ordering::less :
                      std::strong_ordering::greater;
}

template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
std::strong_ordering FixedString<AMaxSize>::operator<=>(const auto& rhs) const noexcept // clang-format on
    requires(std::convertible_to<decltype(rhs), std::string_view> and not std::convertible_to<decltype(rhs), ConstPointer>) {
    const std::string_view view = rhs;
    const auto thisLen = Length();
    const auto rhsLen = view.length();
    if (const auto cmp = std::memcmp(fString, view.data(), std::min(thisLen, rhsLen));
        cmp == 0) {
        return thisLen == rhsLen ? std::strong_ordering::equal :
               thisLen < rhsLen  ? std::strong_ordering::less :
                                   std::strong_ordering::greater;
    } else {
        return cmp < 0 ? std::strong_ordering::less :
                         std::strong_ordering::greater;
    }
}

} // namespace MACE::Utility
