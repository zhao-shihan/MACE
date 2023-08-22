#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Data/Model/Field.h++"
#include "MACE/Extension/gslx/index_sequence.h++"

#include <tuple>

namespace MACE::Data::inline Model {

template<class F>
concept FieldSetLike =
    requires {
        typename F::FieldTuple;
        requires
            []<gsl::index... Is>(gslx::index_sequence<Is...>) {
                return (... and
                        requires {
                            typename F::template Field<Is>;
#if not(defined __GNUC__ and not defined __clang__) // GCC internal compiler error.
                            requires Concept::InstantiatedFrom<typename F::template Field<Is>, Field>;
#endif
                        });
            }(gslx::make_index_sequence<std::tuple_size_v<typename F::FieldTuple>>{});
    };

} // namespace MACE::Data::inline Model
