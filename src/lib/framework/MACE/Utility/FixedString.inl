namespace MACE::inline Utility {

template<std::size_t AMaxSize>
FixedString<AMaxSize>::FixedString() noexcept :
    fData{'\0'} {}

// template<std::size_t AMaxSize>
// FixedString<AMaxSize>::FixedString(char ch) noexcept :
//     fData{ch, '\0'} {}

template<std::size_t AMaxSize>
template<std::size_t N>
FixedString<AMaxSize>::FixedString(const char (&str)[N]) noexcept :
    fData{} {
    constexpr auto maxLength = std::min(N - 1, AMaxSize);
    std::memcpy(fData, str, maxLength);
    fData[maxLength] = '\0';
}

template<std::size_t AMaxSize>
template<std::size_t N>
FixedString<AMaxSize>::FixedString(const FixedString<N>& str) noexcept :
    FixedString(str.Data()) {}

template<std::size_t AMaxSize>
FixedString<AMaxSize>::FixedString(std::string_view str) noexcept :
    fData{} {
    const auto length = std::min(str.length(), AMaxSize);
    std::memcpy(fData, str.data(), length);
    fData[length] = '\0';
}

template<std::size_t AMaxSize>
FixedString<AMaxSize>::FixedString(auto&& str) noexcept
    requires std::same_as<std::remove_cvref_t<decltype(str)>, gsl::zstring> or
             std::same_as<std::remove_cvref_t<decltype(str)>, gsl::czstring> or
             (std::convertible_to<decltype(str), gsl::czstring> and // clang-format off
              not std::convertible_to<decltype(str), std::string_view>) : // clang-format on
    fData{} {
    std::strncpy(fData, str, AMaxSize);
    fData[AMaxSize] = '\0';
}

template<std::size_t AMaxSize>
FixedString<AMaxSize>::FixedString(auto&& str) noexcept
    requires std::convertible_to<decltype(str), std::string> and
             (not std::convertible_to<decltype(str), std::string_view>) and // clang-format off
             (not std::convertible_to<decltype(str), gsl::czstring>) : // clang-format on
    fData{} {
    const std::string string = std::forward<decltype(str)>(str);
    const auto length = std::min(string.length(), AMaxSize);
    std::memcpy(fData, string.c_str(), length);
    fData[length] = '\0';
}

// template<std::size_t AMaxSize>
// FixedString<AMaxSize>& FixedString<AMaxSize>::operator=(char ch) & noexcept {
//     fData = {ch, '\0'};
//     return *this;
// }

template<std::size_t AMaxSize>
template<std::size_t N>
auto FixedString<AMaxSize>::operator=(const char (&rhs)[N]) & noexcept -> FixedString<AMaxSize>& {
    if (N != AMaxSize ? true : (&fData != &rhs)) {
        constexpr auto maxLength = std::min(N - 1, AMaxSize);
        std::memcpy(fData, rhs, maxLength);
        fData[maxLength] = '\0';
    }
    return *this;
}

template<std::size_t AMaxSize>
auto FixedString<AMaxSize>::operator=(std::string_view rhs) & noexcept -> FixedString<AMaxSize>& {
    const auto length = std::min(rhs.length(), AMaxSize);
    std::memmove(fData, rhs.data(), length);
    fData[length] = '\0';
    return *this;
}

template<std::size_t AMaxSize>
auto FixedString<AMaxSize>::operator=(auto&& rhs) & noexcept -> FixedString<AMaxSize>&
    requires std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::zstring> or
             std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::czstring> or
             (std::convertible_to<decltype(rhs), gsl::czstring> and
              not std::convertible_to<decltype(rhs), std::string_view>)
{
    const gsl::czstring cstr = std::forward<decltype(rhs)>(rhs);
    if (fData != cstr) {
        if (std::abs(ConstBegin() - cstr) > AMaxSize) {
            std::strncpy(fData, cstr, AMaxSize);
        } else {
            char copy[AMaxSize + 1];
            std::strncpy(copy, cstr, AMaxSize);
            std::strncpy(fData, copy, AMaxSize);
        }
        fData[AMaxSize] = '\0';
    }
    return *this;
}

template<std::size_t AMaxSize>
auto FixedString<AMaxSize>::operator=(auto&& rhs) & noexcept -> FixedString<AMaxSize>&
    requires std::convertible_to<decltype(rhs), std::string> and
             (not std::convertible_to<decltype(rhs), std::string_view>) and
             (not std::convertible_to<decltype(rhs), gsl::czstring>)
{
    const std::string string = std::forward<decltype(rhs)>(rhs);
    const auto length = std::min(string.length(), AMaxSize);
    std::memcpy(fData, string.c_str(), length);
    fData[length] = '\0';
    return *this;
}

// template<std::size_t AMaxSize>
// FixedString<AMaxSize>& FixedString<AMaxSize>::Append(char ch) noexcept {
//     auto tail = End();
//     *tail = ch;
//     *++tail = '\0';
//     return *this;
// }

template<std::size_t AMaxSize>
template<std::size_t N>
auto FixedString<AMaxSize>::Append(const char (&str)[N]) noexcept -> FixedString<AMaxSize>& {
    const auto length = Length();
    const auto end = Begin() + length;
    const auto count = std::min(N - 1, AMaxSize - length);
    std::memmove(end, str, count);
    end[count] = '\0';
    return *this;
}

template<std::size_t AMaxSize>
auto FixedString<AMaxSize>::Append(std::string_view str) noexcept -> FixedString<AMaxSize>& {
    const auto length = Length();
    const auto end = Begin() + length;
    const auto count = std::min(str.length(), AMaxSize - length);
    std::memmove(end, str.data(), count);
    end[count] = '\0';
    return *this;
}

template<std::size_t AMaxSize>
auto FixedString<AMaxSize>::Append(auto&& str) noexcept -> FixedString<AMaxSize>&
    requires std::same_as<std::remove_cvref_t<decltype(str)>, gsl::zstring> or
             std::same_as<std::remove_cvref_t<decltype(str)>, gsl::czstring> or
             (std::convertible_to<decltype(str), gsl::czstring> and
              not std::convertible_to<decltype(str), std::string_view>)
{
    const gsl::czstring cstr = std::forward<decltype(str)>(str);
    const auto length = Length();
    if (std::abs(ConstBegin() - cstr) > AMaxSize) {
        std::strncat(Begin() + length, cstr, AMaxSize - length);
    } else {
        char copy[AMaxSize + 1];
        std::strncpy(copy, cstr, AMaxSize);
        std::strncat(Begin() + length, copy, AMaxSize - length);
    }
    return *this;
}

template<std::size_t AMaxSize>
auto FixedString<AMaxSize>::Append(auto&& str) noexcept -> FixedString<AMaxSize>&
    requires std::convertible_to<decltype(str), std::string> and
             (not std::convertible_to<decltype(str), std::string_view>) and
             (not std::convertible_to<decltype(str), gsl::czstring>)
{
    const std::string string = std::forward<decltype(str)>(str);
    const auto length = Length();
    const auto end = Begin() + length;
    const auto count = std::min(string.length(), AMaxSize - length);
    std::memcpy(end, string.c_str(), count);
    end[count] = '\0';
    return *this;
}

template<std::size_t AMaxSize>
template<std::size_t N>
auto FixedString<AMaxSize>::operator<=>(const char (&rhs)[N]) const noexcept -> std::strong_ordering {
    const auto cmp = std::strncmp(fData, rhs, std::min(N, AMaxSize + 1));
    return cmp == 0 ? std::strong_ordering::equal :
           cmp < 0  ? std::strong_ordering::less :
                      std::strong_ordering::greater;
}

template<std::size_t AMaxSize>
auto FixedString<AMaxSize>::operator<=>(auto&& rhs) const noexcept -> std::strong_ordering
    requires std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::zstring> or
             std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::czstring> or
             (std::convertible_to<decltype(rhs), gsl::czstring> and
              not std::convertible_to<decltype(rhs), std::string_view>)
{
    const gsl::czstring cstr = std::forward<decltype(rhs)>(rhs);
    const auto cmp = std::strncmp(fData, cstr, AMaxSize + 1);
    return cmp == 0 ? std::strong_ordering::equal :
           cmp < 0  ? std::strong_ordering::less :
                      std::strong_ordering::greater;
}

} // namespace MACE::inline Utility
