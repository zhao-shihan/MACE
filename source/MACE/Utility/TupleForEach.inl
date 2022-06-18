namespace MACE::Utility {

template<template<typename... T> class TupleTT, class FunctorT, typename... ElementT>
requires std::derived_from<TupleTT<ElementT...>, std::tuple<ElementT...>>
class TupleForEachImpl {
    using TupleSize = std::integral_constant<std::size_t, sizeof...(ElementT)>;
    using TupleT = TupleTT<ElementT...>;

    template<typename TupleCVRefT, std::size_t... IndexV>
    requires std::same_as<std::remove_cvref_t<TupleCVRefT>, TupleT>
    constexpr void Impl(TupleCVRefT&& tuple, FunctorT&& func, std::index_sequence<IndexV...>&&) const {
        (func(std::get<IndexV>(std::forward<TupleCVRefT>(tuple))), ...);
    }

public:
    template<typename TupleCVRefT>
    // clang-format off
        requires (std::is_reference_v<TupleCVRefT> and std::same_as<std::remove_cvref_t<TupleCVRefT>, TupleT>)
    constexpr void operator()(TupleCVRefT&& tuple, FunctorT&& func) const {
        // clang-format on
        Impl(std::forward<TupleCVRefT>(tuple), std::forward<FunctorT>(func), std::make_index_sequence<TupleSize::value>());
    }
};

template<template<typename... T> class TupleTT, class FunctorT, typename... ElementT>
requires std::derived_from<std::tuple<ElementT...>, TupleTT<ElementT...>>
constexpr void TupleForEach(const TupleTT<ElementT...>& tuple, FunctorT&& func) {
    TupleForEachImpl<TupleTT, FunctorT, ElementT...>()(tuple, std::forward<FunctorT>(func));
}

template<template<typename... T> class TupleTT, class FunctorT, typename... ElementT>
requires std::derived_from<std::tuple<ElementT...>, TupleTT<ElementT...>>
constexpr void TupleForEach(TupleTT<ElementT...>& tuple, FunctorT&& func) {
    TupleForEachImpl<TupleTT, FunctorT, ElementT...>()(tuple, std::forward<FunctorT>(func));
}

template<template<typename... T> class TupleTT, class FunctorT, typename... ElementT>
requires std::derived_from<std::tuple<ElementT...>, TupleTT<ElementT...>>
constexpr void TupleForEach(TupleTT<ElementT...>&& tuple, FunctorT&& func) {
    TupleForEachImpl<TupleTT, FunctorT, ElementT...>()(tuple, std::forward<FunctorT>(func));
}

} // namespace MACE::Utility
