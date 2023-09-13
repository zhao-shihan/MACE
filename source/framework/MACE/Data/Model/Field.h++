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

namespace MACE::Data::inline Model {

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

} // namespace detail

template<typename T>
concept GoodFieldValueType =
    [] {
        if constexpr (Concept::ROOTFundamental<T>) {
            return not std::same_as<std::decay_t<T>, gsl::zstring>;
        }
        if constexpr (detail::IsStdArray<T>{}) {
            return Concept::ROOTFundamental<typename T::value_type> and
                   not std::same_as<std::decay_t<typename T::value_type>, gsl::zstring>;
        }
        if constexpr (detail::IsFixedString<T>{}) {
            return true;
        }
        return std::is_class_v<T>;
    }();

template<GoodFieldValueType T>
class Field final : public NonConstructibleBase {
public:
    using Type = T;

public:
    template<typename AFieldSet, gsl::index>
    class [[nodiscard]] Signed final {
    public:
        using Type = T;

    public:
        constexpr Signed() = default;
        constexpr Signed(const T& object);
        constexpr Signed(T&& object);

        constexpr Signed(auto&& v)
            requires requires { VectorCast<T>(std::forward<decltype(v)>(v)); };
        constexpr auto operator=(auto&& v) -> Signed&
            requires requires(T fObject) { VectorAssign(fObject, std::forward<decltype(v)>(v)); };

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
        static auto ResetName() -> void { fgName = DefaultName(); }
        static auto ResetTitle() -> void { fgTitle = DefaultTitle(); }

    private:
        static constexpr auto DefaultName() -> std::string_view;
        static constexpr auto DefaultTitle() -> std::string_view;

    private:
        T fObject;

        static std::string fgName;
        static std::string fgTitle;
    };
};

} // namespace MACE::Data::inline Model

#define MACE_DATA_MODEL_FIELD_DECLARE_FIELD_NAME_TITLE(TheField, nameString, titleString) \
    namespace MACE::Data::inline Model {                                                  \
    template<>                                                                            \
    template<>                                                                            \
    std::string TheField::fgName;                                                         \
    template<>                                                                            \
    template<>                                                                            \
    std::string TheField::fgTitle;                                                        \
    template<>                                                                            \
    template<>                                                                            \
    constexpr auto TheField::DefaultName() -> std::string_view { return nameString; }     \
    template<>                                                                            \
    template<>                                                                            \
    constexpr auto TheField::DefaultTitle() -> std::string_view { return titleString; }   \
    }

#include "MACE/Data/Model/Field.inl"
