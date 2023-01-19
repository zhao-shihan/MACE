#pragma once

#include <concepts>
#include <cstdint>
#include <tuple>
#include <utility>

namespace MACE::Utility {

template<std::intmax_t Begin, std::intmax_t End,
         template<std::intmax_t, typename...> class, typename...>
    requires(Begin >= End)
constexpr void StaticForEach(auto&&...) {}

template<std::intmax_t Begin, std::intmax_t End,
         template<std::intmax_t, typename...> class AFunctor, typename... AFunctorArgs>
    requires(Begin < End and std::default_initializable<AFunctor<Begin, AFunctorArgs...>>)
constexpr void StaticForEach(auto&&... args) {
    AFunctor<Begin, AFunctorArgs...>()(std::forward<decltype(args)>(args)...);
    StaticForEach<Begin + 1, End,
                  AFunctor, AFunctorArgs...>(std::forward<decltype(args)>(args)...);
}

} // namespace MACE::Utility
