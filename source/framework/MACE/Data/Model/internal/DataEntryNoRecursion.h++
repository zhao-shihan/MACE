#pragma once

#include "MACE/Extension/gslx/index_sequence.h++"

#include "gsl/gsl"

#include <concepts>
#include <type_traits>

namespace MACE::Data::inline Model::internal {

template<typename E>
concept DataEntryNoRecursion =
    requires {
        typename E::Model;
        typename E::Model::Entry;
        requires std::same_as<E, typename E::Model::Entry>;
        requires
            []<gsl::index... Is>(gslx::index_sequence<Is...>) {
                return (... and
                        requires(const E ce, E e) {
#if not(defined __GNUC__ and not defined __clang__) // GCC internal compiler error.
                            { ce.template Get<typename E::Model::template Field<Is>>() } -> std::same_as<const typename E::Model::template Field<Is>&>;
                            { ce.template Get<Is>() } -> std::same_as<const typename E::Model::template Field<Is>&>;
                            { e.template Get<typename E::Model::template Field<Is>>() } -> std::same_as<typename E::Model::template Field<Is>&>;
                            { e.template Get<Is>() } -> std::same_as<typename E::Model::template Field<Is>&>;
#else // clang-format off
                            ce.template Get<typename E::Model::template Field<Is>>();
                            ce.template Get<Is>();
                            e.template Get<typename E::Model::template Field<Is>>();
                            e.template Get<Is>();
#endif // clang-format on
                        });
            }(gslx::make_index_sequence<E::Model::NField()>{});
        { E::NField() } -> std::same_as<std::size_t>;
        requires E::NField() == E::Model::NField();
    };

} // namespace MACE::Data::inline Model::internal
