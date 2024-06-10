#include "MACE/Utility/ParseEnv.h++"

#include "gsl/gsl"

#include "fmt/core.h"

#include <cstdlib>
#include <stdexcept>
#include <utility>

namespace MACE::inline Utility {

namespace internal {
namespace {

template<muc::ceta_string AOption>
auto ParseEnvImpl(std::string& str, std::size_t pos) -> std::string& {
    const auto dollar{str.find_first_of('$', pos)};
    if (dollar == std::string::npos) { return str; }
    const auto lBrace{dollar + 1};
    if (str[lBrace] != '{') {
        throw std::runtime_error{"MACE::ParseEnv: Environment variable must be provided in the form of ${...}"};
    }
    const auto rBrace{str.find_first_of('}', dollar + 2)};
    if (rBrace == std::string::npos) {
        throw std::runtime_error{"MACE::ParseEnv: Brace not closed"};
    }
    const auto envVar{str.substr(lBrace + 1, rBrace)};
    gsl::czstring env{std::getenv(envVar.c_str())};
    if (env == nullptr) {
        if constexpr (AOption == "Exception") {
            throw std::runtime_error{fmt::format("MACE::ParseEnv: Environment variable '{}' is not set or invalid", envVar)};
        } else if constexpr (AOption == "Ignore") {
            env = "";
        } else {
            static_assert("MACE::ParseEnv: Option can be \"Exception\" or \"Ignore\"");
        }
    }
    str.replace(dollar, rBrace - dollar + 1, env);
    return ParseEnvImpl<AOption>(str, rBrace + 1);
}

} // namespace
} // namespace internal

template<muc::ceta_string AOption>
auto ParseEnv(std::string str) -> std::string {
    return std::move(internal::ParseEnvImpl<AOption>(str, 0));
}

template auto ParseEnv<"Exception">(std::string) -> std::string;
template auto ParseEnv<"Ignore">(std::string) -> std::string;

} // namespace MACE::inline Utility
