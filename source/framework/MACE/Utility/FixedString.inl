namespace MACE::Utility {

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0) // clang-format off
FixedString<AMaxSize>::FixedString() noexcept :
    fData{'\0'} {} // clang-format on

// template<std::size_t AMaxSize>
//     requires((AMaxSize + 1) % alignof(void*) == 0) // clang-format off
// FixedString<AMaxSize>::FixedString(char ch) noexcept :
//     fData{ch, '\0'} {} // clang-format on

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0)
template<std::size_t N>
FixedString<AMaxSize>::FixedString(const char (&str)[N]) noexcept :
    fData{} {
    constexpr auto maxLength = std::min(N - 1, AMaxSize);
    std::memcpy(fData, str, maxLength);
    fData[maxLength] = '\0';
}

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0)
template<std::size_t N>
    requires(N != AMaxSize) // clang-format off
FixedString<AMaxSize>::FixedString(const FixedString<N>& str) noexcept :
    FixedString(str.fData) {} // clang-format on

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0) // clang-format off
FixedString<AMaxSize>::FixedString(std::string_view str) noexcept :
    fData{} { // clang-format on
    const auto length = std::min(str.length(), AMaxSize);
    std::memcpy(fData, str.data(), length);
    fData[length] = '\0';
}

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0) // clang-format off
FixedString<AMaxSize>::FixedString(auto&& str) noexcept // clang-format on
    requires(std::same_as<std::remove_cvref_t<decltype(str)>, gsl::zstring> or
             std::same_as<std::remove_cvref_t<decltype(str)>, gsl::czstring> or
             (std::convertible_to<decltype(str), gsl::czstring> and
              not std::convertible_to<decltype(str), std::string_view>)) :
    fData{} {
    std::strncpy(fData, str, AMaxSize);
    fData[AMaxSize] = '\0';
}

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0) // clang-format off
FixedString<AMaxSize>::FixedString(auto&& str) noexcept // clang-format on
    requires(std::convertible_to<decltype(str), std::string> and
             not std::convertible_to<decltype(str), std::string_view> and
             not std::convertible_to<decltype(str), gsl::czstring>) :
    fData{} {
    const std::string string = std::forward<decltype(str)>(str);
    const auto length = std::min(string.length(), AMaxSize);
    std::memcpy(fData, string.c_str(), length);
    fData[length] = '\0';
}

// template<std::size_t AMaxSize> // clang-format off
//     requires((AMaxSize + 1) % alignof(void*) == 0)
// FixedString<AMaxSize>& FixedString<AMaxSize>::operator=(char ch) & noexcept { // clang-format on
//     fData = {ch, '\0'};
//     return *this;
// }

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0)
template<std::size_t N>
FixedString<AMaxSize>& FixedString<AMaxSize>::operator=(const char (&rhs)[N]) noexcept {
    if (N != AMaxSize ? true : (&fData != &rhs)) {
        constexpr auto maxLength = std::min(N - 1, AMaxSize);
        std::memcpy(fData, rhs, maxLength);
        fData[maxLength] = '\0';
    }
    return *this;
}

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0) // clang-format off
FixedString<AMaxSize>& FixedString<AMaxSize>::operator=(std::string_view rhs) & noexcept { // clang-format on
    const auto length = std::min(rhs.length(), AMaxSize);
    std::memmove(fData, rhs.data(), length);
    fData[length] = '\0';
    return *this;
}

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0) // clang-format off
FixedString<AMaxSize>& FixedString<AMaxSize>::operator=(auto&& rhs) & noexcept // clang-format on
    requires(std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::zstring> or
             std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::czstring> or
             (std::convertible_to<decltype(rhs), gsl::czstring> and
              not std::convertible_to<decltype(rhs), std::string_view>)) {
    const gsl::czstring cstr = std::forward<decltype(rhs)>(rhs);
    if (fData != cstr) {
        if (std::cmp_greater(std::distance(ConstBegin(), cstr), AMaxSize)) {
            std::strncpy(fData, cstr, AMaxSize);
        } else {
            const FixedString<AMaxSize> copy = cstr;
            std::strncpy(fData, copy.fData, AMaxSize);
        }
        fData[AMaxSize] = '\0';
    }
    return *this;
}

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0) // clang-format off
FixedString<AMaxSize>& FixedString<AMaxSize>::operator=(auto&& rhs) & noexcept // clang-format on
    requires(std::convertible_to<decltype(rhs), std::string> and
             not std::convertible_to<decltype(rhs), std::string_view> and
             not std::convertible_to<decltype(rhs), gsl::czstring>) {
    const std::string string = std::forward<decltype(rhs)>(rhs);
    const auto length = std::min(string.length(), AMaxSize);
    std::memcpy(fData, string.c_str(), length);
    fData[length] = '\0';
    return *this;
}

// template<std::size_t AMaxSize> // clang-format off
//     requires((AMaxSize + 1) % alignof(void*) == 0)
// FixedString<AMaxSize>& FixedString<AMaxSize>::Append(char ch) noexcept { // clang-format on
//     auto tail = End();
//     *tail = ch;
//     *++tail = '\0';
//     return *this;
// }

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0)
template<std::size_t N>
FixedString<AMaxSize>& FixedString<AMaxSize>::Append(const char (&str)[N]) noexcept {
    const auto length = Length();
    const auto end = Begin() + length;
    const auto count = std::min(N - 1, AMaxSize - length);
    std::memmove(end, str, count);
    end[count] = '\0';
    return *this;
}

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0) // clang-format off
FixedString<AMaxSize>& FixedString<AMaxSize>::Append(std::string_view str) noexcept { // clang-format on
    const auto length = Length();
    const auto end = Begin() + length;
    const auto count = std::min(str.length(), AMaxSize - length);
    std::memmove(end, str.data(), count);
    end[count] = '\0';
    return *this;
}

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0) // clang-format off
FixedString<AMaxSize>& FixedString<AMaxSize>::Append(auto&& str) noexcept // clang-format on
    requires(std::same_as<std::remove_cvref_t<decltype(str)>, gsl::zstring> or
             std::same_as<std::remove_cvref_t<decltype(str)>, gsl::czstring> or
             (std::convertible_to<decltype(str), gsl::czstring> and
              not std::convertible_to<decltype(str), std::string_view>)) {
    const gsl::czstring cstr = std::forward<decltype(str)>(str);
    const auto length = Length();
    if (std::cmp_greater(std::distance(ConstBegin(), cstr), AMaxSize)) {
        std::strncat(Begin() + length, cstr, AMaxSize - length);
    } else {
        const FixedString<AMaxSize> copy = cstr;
        std::strncat(Begin() + length, copy.fData, AMaxSize - length);
    }
    return *this;
}

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0) // clang-format off
FixedString<AMaxSize>& FixedString<AMaxSize>::Append(auto&& str) noexcept // clang-format on
    requires(std::convertible_to<decltype(str), std::string> and
             not std::convertible_to<decltype(str), std::string_view> and
             not std::convertible_to<decltype(str), gsl::czstring>) {
    const std::string string = std::forward<decltype(str)>(str);
    const auto length = Length();
    const auto end = Begin() + length;
    const auto count = std::min(string.length(), AMaxSize - length);
    std::memcpy(end, string.c_str(), count);
    end[count] = '\0';
    return *this;
}

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0)
template<std::size_t N>
std::strong_ordering FixedString<AMaxSize>::operator<=>(const char (&rhs)[N]) const noexcept {
    const auto cmp = std::strncmp(fData, rhs, std::min(N, AMaxSize + 1));
    return cmp == 0 ? std::strong_ordering::equal :
           cmp < 0  ? std::strong_ordering::less :
                      std::strong_ordering::greater;
}

template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0) // clang-format off
std::strong_ordering FixedString<AMaxSize>::operator<=>(auto&& rhs) const noexcept // clang-format on
    requires(std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::zstring> or
             std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::czstring> or
             (std::convertible_to<decltype(rhs), gsl::czstring> and
              not std::convertible_to<decltype(rhs), std::string_view>)) {
    const gsl::czstring cstr = std::forward<decltype(rhs)>(rhs);
    const auto cmp = std::strncmp(fData, cstr, AMaxSize + 1);
    return cmp == 0 ? std::strong_ordering::equal :
           cmp < 0  ? std::strong_ordering::less :
                      std::strong_ordering::greater;
}

} // namespace MACE::Utility
