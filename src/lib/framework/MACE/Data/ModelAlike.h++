#pragma once

#include "MACE/Data/ValidModel.h++"
#include "MACE/Extension/gslx/index_sequence.h++"

#include "gsl/gsl"

#include <algorithm>
#include <array>

namespace MACE::Data {

template<typename M1, typename M2>
concept ModelAlike = requires {
    requires ValidModel<M1>;
    requires ValidModel<M2>;
    requires M1::NField() >= M2::NField();
    requires(
        []<gsl::index Is...>(gslx::index_sequence<Is...>) {
            return (... and
                    ([]<gsl::index Js...>(gslx::index_sequence<Js...>) {
                        return (... or
                                M1::template Name<Js>() == M2::template Name<Is>());
                    }(gslx::make_index_sequence<M1>{})));
        }(gslx::make_index_sequence<M2>{}));
};

template<typename M1, typename M2>
concept ModelStronglyAlike = requires {
    requires ModelAlike<M1, M2>;
    requires M1::NField() == M2::NField();
};

} // namespace MACE::Data
