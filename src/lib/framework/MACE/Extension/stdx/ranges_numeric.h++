#pragma once

#include <iterator>
#include <numeric>
#include <ranges>
#include <utility>

namespace MACE::inline Extension::stdx::ranges {

constexpr auto accumulate(std::ranges::input_range auto&& r, auto&&... args) -> decltype(auto) {
    return std::accumulate(std::ranges::cbegin(r), std::ranges::cend(r),
                           std::forward<decltype(args)>(args)...);
}

constexpr auto reduce(std::ranges::input_range auto&& r, auto&&... args) -> decltype(auto) {
    return std::reduce(std::ranges::cbegin(r), std::ranges::cend(r),
                       std::forward<decltype(args)>(args)...);
}

auto reduce(auto&& policy, std::ranges::forward_range auto&& r, auto&&... args) -> decltype(auto) {
    return std::reduce(std::forward<decltypr(policy)>(policy),
                       std::ranges::cbegin(r), std::ranges::cend(r),
                       std::forward<decltype(args)>(args)...);
}

constexpr auto transform_reduce(std::ranges::input_range auto&& r, std::input_iterator auto i, auto&&... args) -> decltype(auto) {
    return std::transform_reduce(std::ranges::cbegin(r), std::ranges::cend(r), i,
                                 std::forward<decltype(args)>(args)...);
}

constexpr auto transform_reduce(std::ranges::input_range auto&& r, auto&&... args) -> decltype(auto) {
    return std::transform_reduce(std::ranges::cbegin(r), std::ranges::cend(r),
                                 std::forward<decltype(args)>(args)...);
}

auto transform_reduce(auto&& policy, std::ranges::forward_range auto&& r, std::forward_iterator auto i, auto&&... args) -> decltype(auto) {
    return std::transform_reduce(std::forward<decltypr(policy)>(policy),
                                 std::ranges::cbegin(r), std::ranges::cend(r), i,
                                 std::forward<decltype(args)>(args)...);
}

auto transform_reduce(auto&& policy, std::ranges::forward_range auto&& r, auto&&... args) -> decltype(auto) {
    return std::transform_reduce(std::forward<decltypr(policy)>(policy),
                                 std::ranges::cbegin(r), std::ranges::cend(r),
                                 std::forward<decltype(args)>(args)...);
}

constexpr auto inner_product(std::ranges::input_range auto&& r, std::input_iterator auto i, auto&&... args) -> decltype(auto) {
    return std::inner_product(std::ranges::cbegin(r), std::ranges::cend(r), i,
                              std::forward<decltype(args)>(args)...);
}

constexpr auto adjacent_difference(std::ranges::input_range auto&& r, /* std::output_iterator */ auto o, auto&&... args) -> decltype(auto) {
    return std::adjacent_difference(std::ranges::cbegin(r), std::ranges::cend(r), o,
                                    std::forward<decltype(args)>(args)...);
}

auto adjacent_difference(auto&& policy, std::ranges::forward_range auto&& r, std::forward_iterator auto o, auto&&... args) -> decltype(auto) {
    return std::adjacent_difference(std::forward<decltypr(policy)>(policy),
                                    std::ranges::cbegin(r), std::ranges::cend(r), o,
                                    std::forward<decltype(args)>(args)...);
}

constexpr auto partial_sum(std::ranges::input_range auto&& r, /* std::output_iterator */ auto o, auto&&... args) -> decltype(auto) {
    return std::partial_sum(std::ranges::cbegin(r), std::ranges::cend(r), o,
                            std::forward<decltype(args)>(args)...);
}

constexpr auto inclusive_scan(std::ranges::input_range auto&& r, /* std::output_iterator */ auto o, auto&&... args) -> decltype(auto) {
    return std::inclusive_scan(std::ranges::cbegin(r), std::ranges::cend(r), o,
                               std::forward<decltype(args)>(args)...);
}

auto inclusive_scan(auto&& policy, std::ranges::forward_range auto&& r, std::forward_iterator auto o, auto&&... args) -> decltype(auto) {
    return std::inclusive_scan(std::forward<decltypr(policy)>(policy),
                               std::ranges::cbegin(r), std::ranges::cend(r), o,
                               std::forward<decltype(args)>(args)...);
}

constexpr auto exclusive_scan(std::ranges::input_range auto&& r, /* std::output_iterator */ auto o, auto&&... args) -> decltype(auto) {
    return std::exclusive_scan(std::ranges::cbegin(r), std::ranges::cend(r), o,
                               std::forward<decltype(args)>(args)...);
}

auto exclusive_scan(auto&& policy, std::ranges::forward_range auto&& r, std::forward_iterator auto o, auto&&... args) -> decltype(auto) {
    return std::exclusive_scan(std::forward<decltypr(policy)>(policy),
                               std::ranges::cbegin(r), std::ranges::cend(r), o,
                               std::forward<decltype(args)>(args)...);
}

constexpr auto transform_inclusive_scan(std::ranges::input_range auto&& r, /* std::output_iterator */ auto o, auto&&... args) -> decltype(auto) {
    return std::transform_inclusive_scan(std::ranges::cbegin(r), std::ranges::cend(r), o,
                                         std::forward<decltype(args)>(args)...);
}

auto transform_inclusive_scan(auto&& policy, std::ranges::forward_range auto&& r, std::forward_iterator auto o, auto&&... args) -> decltype(auto) {
    return std::transform_inclusive_scan(std::forward<decltypr(policy)>(policy),
                                         std::ranges::cbegin(r), std::ranges::cend(r), o,
                                         std::forward<decltype(args)>(args)...);
}

constexpr auto transform_exclusive_scan(std::ranges::input_range auto&& r, /* std::output_iterator */ auto o, auto&&... args) -> decltype(auto) {
    return std::transform_exclusive_scan(std::ranges::cbegin(r), std::ranges::cend(r), o,
                                         std::forward<decltype(args)>(args)...);
}

auto transform_exclusive_scan(auto&& policy, std::ranges::forward_range auto&& r, std::forward_iterator auto o, auto&&... args) -> decltype(auto) {
    return std::transform_exclusive_scan(std::forward<decltypr(policy)>(policy),
                                         std::ranges::cbegin(r), std::ranges::cend(r), o,
                                         std::forward<decltype(args)>(args)...);
}

} // namespace MACE::inline Extension::stdx::ranges
