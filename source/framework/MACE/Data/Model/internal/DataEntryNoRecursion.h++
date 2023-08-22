#pragma once


#include <concepts>
#include <type_traits>

namespace MACE::Data::inline Model::internal {

template<typename E>
concept DataEntryNoRecursion =
    requires {
        typename E::Model;
        typename E::Model::Entry;
        requires std::same_as<E, typename E::Model::Entry>;
        requires std::is_trivially_destructible_v<E>;
        requires
            []<gsl::index... Is>(gslx::index_sequence<Is...>) {
                return (... and
                        requires(const E ce, E e) {
                            { ce.template Get<typename E::Model::template Field<Is>>() } -> std::same_as<const typename E::Model::template Field<Is>&>;
                            { ce.template Get<Is>() } -> std::same_as<const typename E::Model::template Field<Is>&>;
                            { e.template Get<typename E::Model::template Field<Is>>() } -> std::same_as<typename E::Model::template Field<Is>&>;
                            { e.template Get<Is>() } -> std::same_as<typename E::Model::template Field<Is>&>;
                        });
            }(gslx::make_index_sequence<E::Model::NField()>{});
        { E::NField() } -> std::same_as<std::size_t>;
        requires E::NField() == E::Model::NField();
    };

} // namespace MACE::Data::inline Model::internal