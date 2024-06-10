#pragma once

#include "muc/ceta_string"

#include <string>

namespace MACE::inline Utility {

/// @brief Parse a string with environment variables (${...}) and replace them with
/// corresponding values. If the string does not contains ${...} then it is returned
/// as is.
/// @tparam AOption Controlling the behavior when any environment variable
/// do not exists. Can be "Exception" (default) or "Ignore".
/// @param str A string with environment variables (${...}).
/// @return Parsed result.
/// @note If an environment variable is not set, the default behavior is to throw
/// an exception ("Exception"). The behavior can be changed to replace them with
/// blank by setting `option` to "Ignore".
/// An environment variable must be surrounded by "${}", $ENV syntax is not supported.
/// @exception std::runtime_error if anything unexcepted happens.
template<muc::ceta_string AOption = "Exception">
auto ParseEnv(std::string str) -> std::string;

} // namespace MACE::inline Utility
