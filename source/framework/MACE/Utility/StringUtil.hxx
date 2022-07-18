#pragma once

#include <concepts>
#include <string>
#include <string_view>
#include <vector>

namespace MACE::Utility {

enum SplitStringOption { kAll,
                         kFirst,
                         kLast };
template<std::constructible_from<std::string_view> AString = std::string_view, SplitStringOption OptionV = kFirst>
std::vector<AString> SplitString(std::string_view string, char delimiter);

} // namespace MACE::Utility

#include "MACE/Utility/StringUtil.inl"
