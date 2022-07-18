namespace MACE::Utility {

template<template<typename... T> class AATuple, class AFunctor, typename... AElement>
requires std::derived_from<AATuple<AElement...>, std::tuple<AElement...>>
class TupleForEachImpl {
    using TupleSize = std::integral_constant<std::size_t, sizeof...(AElement)>;
    using ATuple = AATuple<AElement...>;

    template<typename ATupleCVRef, std::size_t... AIndex>
    requires std::same_as<std::remove_cvref_t<ATupleCVRef>, ATuple>
    constexpr void Impl(ATupleCVRef&& tuple, AFunctor&& func, std::index_sequence<AIndex...>&&) const {
        (func(std::get<AIndex>(std::forward<ATupleCVRef>(tuple))), ...);
    }

public:
    template<typename ATupleCVRef>
    // clang-format off
        requires (std::is_reference_v<ATupleCVRef> and std::same_as<std::remove_cvref_t<ATupleCVRef>, ATuple>)
    constexpr void operator()(ATupleCVRef&& tuple, AFunctor&& func) const {
        // clang-format on
        Impl(std::forward<ATupleCVRef>(tuple), std::forward<AFunctor>(func), std::make_index_sequence<TupleSize::value>());
    }
};

template<template<typename... T> class AATuple, class AFunctor, typename... AElement>
requires std::derived_from<std::tuple<AElement...>, AATuple<AElement...>>
constexpr void TupleForEach(const AATuple<AElement...>& tuple, AFunctor&& func) {
    TupleForEachImpl<AATuple, AFunctor, AElement...>()(tuple, std::forward<AFunctor>(func));
}

template<template<typename... T> class AATuple, class AFunctor, typename... AElement>
requires std::derived_from<std::tuple<AElement...>, AATuple<AElement...>>
constexpr void TupleForEach(AATuple<AElement...>& tuple, AFunctor&& func) {
    TupleForEachImpl<AATuple, AFunctor, AElement...>()(tuple, std::forward<AFunctor>(func));
}

template<template<typename... T> class AATuple, class AFunctor, typename... AElement>
requires std::derived_from<std::tuple<AElement...>, AATuple<AElement...>>
constexpr void TupleForEach(AATuple<AElement...>&& tuple, AFunctor&& func) {
    TupleForEachImpl<AATuple, AFunctor, AElement...>()(tuple, std::forward<AFunctor>(func));
}

} // namespace MACE::Utility
