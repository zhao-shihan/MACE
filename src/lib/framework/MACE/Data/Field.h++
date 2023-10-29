#pragma once

#include "MACE/Concept/ROOTFundamental.h++"
#include "MACE/Data/CEvalNTSTA.h++"
#include "MACE/Utility/FixedString.h++"
#include "MACE/Utility/NonConstructibleBase.h++"
#include "MACE/Utility/VectorAssign.h++"
#include "MACE/Utility/VectorCast.h++"

#include "gsl/gsl"

#include "fmt/format.h"

#include <array>
#include <cinttypes>
#include <concepts>
#include <memory>
#include <type_traits>
#include <utility>

namespace MACE::Data {

namespace internal {

template<typename>
struct IsStdArray
    : std::false_type {};
template<typename T, std::size_t N>
struct IsStdArray<std::array<T, N>>
    : std::true_type {};

template<typename>
struct IsFixedString
    : std::false_type {};
template<std::size_t N>
struct IsFixedString<FixedString<N>>
    : std::true_type {};

} // namespace internal

template<typename T>
concept GoodFieldValueType =
    [] {
        if constexpr (Concept::ROOTFundamental<T>) {
            return not std::same_as<std::decay_t<T>, gsl::zstring>;
        }
        if constexpr (internal::IsStdArray<T>{}) {
            return Concept::ROOTFundamental<typename T::value_type> and
                   not std::same_as<std::decay_t<typename T::value_type>, gsl::zstring>;
        }
        if constexpr (internal::IsFixedString<T>{}) {
            return true;
        }
        return std::is_class_v<T>;
    }();

template<GoodFieldValueType T, CEvalNTSTA AName, CEvalNTSTA ATitle = nullptr>
class [[nodiscard]] Field final {
public:
    using Type = T;

public:
    constexpr Field() = default;
    constexpr Field(const T& object);
    constexpr Field(T&& object);
    template<typename U>
        requires(std::constructible_from<T, U> and not std::same_as<std::remove_cvref_t<U>, T>)
    constexpr Field(U&& object);

    template<typename U>
        requires(internal::IsStdArray<T>::value and not std::constructible_from<T, U> and not std::same_as<std::remove_cvref_t<U>, T> and
                 requires(U&& object) { VectorCast<T>(std::forward<U>(object)); })
    constexpr Field(U&& object);
    template<typename U>
        requires(internal::IsStdArray<T>::value and not std::constructible_from<T, U> and not std::same_as<std::remove_cvref_t<U>, T> and
                 requires(T fObject, U&& object) { VectorAssign(fObject, std::forward<U>(object)); })
    constexpr auto operator=(U&& object) -> auto&;

    constexpr operator T&() & { return fObject; }
    constexpr operator const T&() const& { return fObject; }
    constexpr operator T() && { return std::move(fObject); }

    constexpr auto operator()() & -> auto& { return fObject; }
    constexpr auto operator()() const& -> const auto& { return fObject; }
    constexpr auto operator()() && -> auto { return std::move(fObject); }

    template<typename U>
    constexpr auto As() const& -> std::conditional_t<std::same_as<T, U>, const T&, U>;
    template<typename U>
    constexpr auto As() && -> U;

    constexpr auto operator[](auto&& i) const& -> decltype(std::declval<const T&>()[std::forward<decltype(i)>(i)])
        requires requires(const T fObject) { fObject[std::forward<decltype(i)>(i)]; }
    { return fObject[std::forward<decltype(i)>(i)]; }
    constexpr auto operator[](auto&& i) && -> decltype(std::declval<T>()[std::forward<decltype(i)>(i)])
        requires requires(T fObject) { std::move(fObject)[std::forward<decltype(i)>(i)]; }
    { return std::move(fObject)[std::forward<decltype(i)>(i)]; }

    static constexpr auto Name() -> const auto& { return AName; }
    static constexpr auto Title() -> const auto& { return ATitle; }

private:
    T fObject;
};

} // namespace MACE::Data

#include "MACE/Data/Field.inl"
