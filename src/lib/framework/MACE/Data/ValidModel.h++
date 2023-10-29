#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Data/Model.h++"
#include "MACE/Extension/gslx/index_sequence.h++"

#include <algorithm>

namespace MACE::Data {

template<typename M>
concept ValidModel = requires {
    requires Concept::InstantiatedFrom<M, Model>;
    // no duplicate names
    requires(
        []<gsl::index... Is>(gslx::index_sequence<Is...>) {
            return (... and
                    ([]<gsl::index... Js>(const auto& name, const auto i,
                                          gslx::index_sequence<Js...>) {
                        return (... and not(name == M::template Field<Js>::Name() xor i == Js));
                    }(M::template Field<Is>::Name(), Is,
                      gslx::make_index_sequence<M::NField()>{})));
        }(gslx::make_index_sequence<M::NField()>{}));
};

} // namespace MACE::Data
