#pragma once

#include "MACE/Concept/ROOTFundamental.h++"
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
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace MACE::Data::inline Model::inline Field {

namespace detail {

template<typename T>
struct IsStdArray
    : std::false_type {};

template<typename T, std::size_t N>
struct IsStdArray<std::array<T, N>>
    : std::true_type {};

template<typename T>
struct IsFixedString
    : std::false_type {};

template<std::size_t N>
struct IsFixedString<FixedString<N>>
    : std::true_type {};

template<typename T, typename U>
concept VeryDifferentFrom = not std::same_as<std::decay_t<T>, U>;

} // namespace detail

template<typename T>
concept GoodFieldValueType =
    (Concept::ROOTFundamental<T> and not std::same_as<T, gsl::zstring>) or
    (detail::IsStdArray<T>::value and Concept::ROOTFundamental<typename T::value_type> and not std::same_as<typename T::value_type, gsl::zstring>) or
    detail::IsFixedString<T>::value or
    std::is_class_v<T>;

template<GoodFieldValueType T>
class BasicField final : public NonConstructibleBase {
public:
    using Type = T;

public:
    template<typename AFieldSet, gsl::index>
    class Named final {
    public:
        using Type = T;

    public:
        constexpr Named() = default;
        constexpr Named(const T& object);
        constexpr Named(T&& object);

        constexpr auto operator=(detail::VeryDifferentFrom<Named> auto&& o) & -> auto&;

        constexpr operator T&() { return fObject; }
        constexpr operator const T&() const { return fObject; }

        constexpr auto operator()() -> T& { return fObject; }
        constexpr auto operator()() const -> const T& { return fObject; }

        template<typename U>
        constexpr auto As() const -> std::conditional_t<std::same_as<T, U>, const T&, U>;

        static auto Name() -> const auto& { return fgName; }
        static auto Title() -> const auto& { return fgTitle; }
        static auto Name(std::string_view name) -> void { fgName = name; }
        static auto Title(std::string_view title) -> void { fgTitle = title; }
        static auto ResetName() -> void { fgName = fgDefaultName; }
        static auto ResetTitle() -> void { fgTitle = fgDefaultTitle; }

    private:
        T fObject;

        static std::string fgName;
        static std::string fgTitle;
        static const std::string fgDefaultName;
        static const std::string fgDefaultTitle;
    };
};

#define MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(TheField) \
    template<>                                                   \
    template<>                                                   \
    std::string TheField::fgName;                                \
    template<>                                                   \
    template<>                                                   \
    std::string TheField::fgTitle;                               \
    template<>                                                   \
    template<>                                                   \
    const std::string TheField::fgDefaultName;                   \
    template<>                                                   \
    template<>                                                   \
    const std::string TheField::fgDefaultTitle;

#define MACE_DATA_MODEL_FIELD_DEFINE_FIELD_NAME_TITLE(TheField, nameString, titleString) \
    template<>                                                                           \
    template<>                                                                           \
    std::string TheField::fgName = nameString;                                           \
    template<>                                                                           \
    template<>                                                                           \
    std::string TheField::fgTitle = titleString;                                         \
    template<>                                                                           \
    template<>                                                                           \
    const std::string TheField::fgDefaultName = nameString;                              \
    template<>                                                                           \
    template<>                                                                           \
    const std::string TheField::fgDefaultTitle = titleString;

} // namespace MACE::Data::inline Model::inline Field

#include "MACE/Data/Model/Field/BasicField.inl"
