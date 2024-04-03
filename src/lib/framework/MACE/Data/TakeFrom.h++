#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Data/internal/TypeTraits.h++"
#include "MACE/Extension/ROOTX/RDataFrame.h++"
#include "MACE/Extension/gslx/index_sequence.h++"
#include "MACE/Utility/NonConstructibleBase.h++"

#include "ROOT/RVec.hxx"

#include "gsl/gsl"

#include <concepts>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

namespace MACE::Data {

template<TupleModelizable... Ts>
class Take : public NonConstructibleBase {
public:
    static auto From(ROOTX::RDataFrame auto&& dataframe) -> std::vector<std::shared_ptr<Tuple<Ts...>>>;

private:
    template<gsl::index... Is>
    class TakeOne;

    template<gsl::index... Is>
    TakeOne(std::vector<std::shared_ptr<Tuple<Ts...>>>, gslx::index_sequence<Is...>) -> TakeOne<Is...>;
};

} // namespace MACE::Data

#include "MACE/Data/TakeFrom.inl"
