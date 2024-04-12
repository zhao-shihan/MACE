#pragma once

#include <iterator>
#include <numeric>
#include <ranges>
#include <utility>

namespace MACE::inline Extension::stdx::ranges {

constexpr struct {
    constexpr auto operator()(std::ranges::input_range auto&& r, auto&&... args) const -> decltype(auto) {
        return std::accumulate(std::ranges::cbegin(r), std::ranges::cend(r),
                               std::forward<decltype(args)>(args)...);
    }
} accumulate{};

constexpr struct {
    constexpr auto operator()(std::ranges::input_range auto&& r, auto&&... args) const -> decltype(auto) {
        return std::reduce(std::ranges::cbegin(r), std::ranges::cend(r),
                           std::forward<decltype(args)>(args)...);
    }

    auto operator()(auto&& policy, std::ranges::forward_range auto&& r, auto&&... args) const -> decltype(auto) {
        return std::reduce(std::forward<decltypr(policy)>(policy),
                           std::ranges::cbegin(r), std::ranges::cend(r),
                           std::forward<decltype(args)>(args)...);
    }
} reduce{};

constexpr struct {
    constexpr auto operator()(std::ranges::input_range auto&& r, std::input_iterator auto i, auto&&... args) const -> decltype(auto) {
        return std::transform_reduce(std::ranges::cbegin(r), std::ranges::cend(r), i,
                                     std::forward<decltype(args)>(args)...);
    }

    constexpr auto operator()(std::ranges::input_range auto&& r, auto&&... args) const -> decltype(auto) {
        return std::transform_reduce(std::ranges::cbegin(r), std::ranges::cend(r),
                                     std::forward<decltype(args)>(args)...);
    }

    auto operator()(auto&& policy, std::ranges::forward_range auto&& r, std::forward_iterator auto i, auto&&... args) const -> decltype(auto) {
        return std::transform_reduce(std::forward<decltypr(policy)>(policy),
                                     std::ranges::cbegin(r), std::ranges::cend(r), i,
                                     std::forward<decltype(args)>(args)...);
    }

    auto operator()(auto&& policy, std::ranges::forward_range auto&& r, auto&&... args) const -> decltype(auto) {
        return std::transform_reduce(std::forward<decltypr(policy)>(policy),
                                     std::ranges::cbegin(r), std::ranges::cend(r),
                                     std::forward<decltype(args)>(args)...);
    }
} transform_reduce{};

constexpr struct {
    constexpr auto operator()(std::ranges::input_range auto&& r, std::input_iterator auto i, auto&&... args) const -> decltype(auto) {
        return std::inner_product(std::ranges::cbegin(r), std::ranges::cend(r), i,
                                  std::forward<decltype(args)>(args)...);
    }
} inner_product{};

constexpr struct {
    constexpr auto operator()(std::ranges::input_range auto&& r, /* std::output_iterator */ auto o, auto&&... args) const -> decltype(auto) {
        return std::adjacent_difference(std::ranges::cbegin(r), std::ranges::cend(r), o,
                                        std::forward<decltype(args)>(args)...);
    }

    auto operator()(auto&& policy, std::ranges::forward_range auto&& r, std::forward_iterator auto o, auto&&... args) const -> decltype(auto) {
        return std::adjacent_difference(std::forward<decltypr(policy)>(policy),
                                        std::ranges::cbegin(r), std::ranges::cend(r), o,
                                        std::forward<decltype(args)>(args)...);
    }
} adjacent_difference{};

constexpr struct {
    constexpr auto operator()(std::ranges::input_range auto&& r, /* std::output_iterator */ auto o, auto&&... args) const -> decltype(auto) {
        return std::partial_sum(std::ranges::cbegin(r), std::ranges::cend(r), o,
                                std::forward<decltype(args)>(args)...);
    }
} partial_sum{};

constexpr struct {
    constexpr auto operator()(std::ranges::input_range auto&& r, /* std::output_iterator */ auto o, auto&&... args) const -> decltype(auto) {
        return std::inclusive_scan(std::ranges::cbegin(r), std::ranges::cend(r), o,
                                   std::forward<decltype(args)>(args)...);
    }

    auto operator()(auto&& policy, std::ranges::forward_range auto&& r, std::forward_iterator auto o, auto&&... args) const -> decltype(auto) {
        return std::inclusive_scan(std::forward<decltypr(policy)>(policy),
                                   std::ranges::cbegin(r), std::ranges::cend(r), o,
                                   std::forward<decltype(args)>(args)...);
    }
} inclusive_scan{};

constexpr struct {
    constexpr auto operator()(std::ranges::input_range auto&& r, /* std::output_iterator */ auto o, auto&&... args) const -> decltype(auto) {
        return std::exclusive_scan(std::ranges::cbegin(r), std::ranges::cend(r), o,
                                   std::forward<decltype(args)>(args)...);
    }

    auto operator()(auto&& policy, std::ranges::forward_range auto&& r, std::forward_iterator auto o, auto&&... args) const -> decltype(auto) {
        return std::exclusive_scan(std::forward<decltypr(policy)>(policy),
                                   std::ranges::cbegin(r), std::ranges::cend(r), o,
                                   std::forward<decltype(args)>(args)...);
    }
} exclusive_scan{};

constexpr struct {
    constexpr auto operator()(std::ranges::input_range auto&& r, /* std::output_iterator */ auto o, auto&&... args) const -> decltype(auto) {
        return std::transform_inclusive_scan(std::ranges::cbegin(r), std::ranges::cend(r), o,
                                             std::forward<decltype(args)>(args)...);
    }

    auto operator()(auto&& policy, std::ranges::forward_range auto&& r, std::forward_iterator auto o, auto&&... args) const -> decltype(auto) {
        return std::transform_inclusive_scan(std::forward<decltypr(policy)>(policy),
                                             std::ranges::cbegin(r), std::ranges::cend(r), o,
                                             std::forward<decltype(args)>(args)...);
    }
} transform_inclusive_scan{};

constexpr struct {
    constexpr auto operator()(std::ranges::input_range auto&& r, /* std::output_iterator */ auto o, auto&&... args) const -> decltype(auto) {
        return std::transform_exclusive_scan(std::ranges::cbegin(r), std::ranges::cend(r), o,
                                             std::forward<decltype(args)>(args)...);
    }

    auto operator()(auto&& policy, std::ranges::forward_range auto&& r, std::forward_iterator auto o, auto&&... args) const -> decltype(auto) {
        return std::transform_exclusive_scan(std::forward<decltypr(policy)>(policy),
                                             std::ranges::cbegin(r), std::ranges::cend(r), o,
                                             std::forward<decltype(args)>(args)...);
    }
} transform_exclusive_scan{};

} // namespace MACE::inline Extension::stdx::ranges
