#include "MACE/Utility/ShortString.hxx"

namespace MACE::Utility {

ShortString::ShortString() noexcept :
    fString{'\0'} {}

ShortString::ShortString(const ShortString& rhs) noexcept :
    ShortString(rhs.fString) {}

ShortString::ShortString(char ch) noexcept :
    fString{ch, '\0'} {}

ShortString& ShortString::operator=(const char* rhs) noexcept {
    if (rhs != fString) {
        std::strncpy(fString, rhs, fgMaxLength);
    }
    return *this;
}

ShortString& ShortString::operator=(char rhs) noexcept {
    const char temp[2] = {rhs, '\0'};
    std::strncpy(fString, temp, fgMaxLength);
    return *this;
}

ShortString& ShortString::operator+=(const char* rhs) noexcept {
    std::strncat(fString, rhs, fgMaxLength);
    return *this;
}

ShortString& ShortString::operator+=(char rhs) noexcept {
    const char temp[2] = {rhs, '\0'};
    std::strncat(fString, temp, 1);
    return *this;
}

std::weak_ordering ShortString::operator<=>(const char* rhs) const noexcept {
    const auto cmpResult = std::strncmp(fString, rhs, fgMaxLength);
    if (cmpResult < 0) {
        return std::weak_ordering::less;
    } else if (cmpResult > 0) {
        return std::weak_ordering::greater;
    } else {
        return std::weak_ordering::equivalent;
    }
}

} // namespace MACE::Utility
