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
        std::strncpy(fString, rhs, fgkMaxLength);
    }
    return *this;
}

ShortString& ShortString::operator=(char rhs) noexcept {
    fString[0] = rhs;
    fString[1] = '\0';
    return *this;
}

ShortString& ShortString::operator+=(const char* rhs) noexcept {
    std::strncat(fString, rhs, fgkMaxLength);
    return *this;
}

ShortString& ShortString::operator+=(char rhs) noexcept {
    auto tail = fString + this->length();
    *tail = rhs;
    *++tail = '\0';
    return *this;
}

std::weak_ordering ShortString::operator<=>(const char* rhs) const noexcept {
    const auto cmpResult = std::strncmp(fString, rhs, fgkMaxLength);
    if (cmpResult < 0) {
        return std::weak_ordering::less;
    } else if (cmpResult > 0) {
        return std::weak_ordering::greater;
    } else {
        return std::weak_ordering::equivalent;
    }
}

} // namespace MACE::Utility
