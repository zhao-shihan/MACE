#pragma once

#include "MACE/Extension/stdx/boolean_testable.h++"
#include "MACE/Extension/stdx/tuple_like.h++"
#include "MACE/Extension/stdx/apply.h++"

#include <utility>

namespace MACE::inline Extension::stdx {

template<typename F, typename T>
concept applicable =
    requires(F&& Func, T&& t) {
        requires tuple_like<T>;
        { apply(std::forward<F>(Func), std::forward<T>(t)) };
    };

template<typename F, typename T>
concept predicate_applicable =
    requires(F&& Func, T&& t) {
        requires tuple_like<T>;
        { apply(std::forward<F>(Func), std::forward<T>(t)) } -> boolean_testable;
    };

} // namespace MACE::inline Extension::stdx
