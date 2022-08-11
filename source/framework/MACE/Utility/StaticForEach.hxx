#pragma once

#include <concepts>
#include <cstdint>
#include <tuple>
#include <utility>

namespace MACE::Utility {

template<std::intmax_t Begin, std::intmax_t End, template<std::intmax_t, typename...> class,
         typename ATiedArgs, typename...> // clang-format off
    requires(Begin >= End)
constexpr void StaticForEach(ATiedArgs&&) {} // clang-format on

template<std::intmax_t Begin, std::intmax_t End, template<std::intmax_t, typename...> class AFunctor,
         typename ATiedArgs, typename... AFunctorTemplateArgs> // clang-format off
    requires(Begin < End and std::default_initializable<AFunctor<Begin, AFunctorTemplateArgs...>>)
constexpr void StaticForEach(ATiedArgs&& argsTuple) { // clang-format on
    std::apply(AFunctor<Begin, AFunctorTemplateArgs...>(), std::forward<ATiedArgs>(argsTuple));
    StaticForEach<Begin + 1, End, AFunctor,
              ATiedArgs, AFunctorTemplateArgs...>(std::forward<ATiedArgs>(argsTuple));
}

} // namespace MACE::Utility
