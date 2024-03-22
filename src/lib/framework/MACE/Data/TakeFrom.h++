#pragma once

#include "MACE/Concept/InstantiatedFrom.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Data/internal/TypeTraits.h++"
#include "MACE/Extension/gslx/index_sequence.h++"
#include "MACE/Utility/NonConstructibleBase.h++"

#include "ROOT/RDF/RInterface.hxx"
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
    static auto From(ROOT::RDF::RNode dataframe) -> std::vector<std::unique_ptr<Tuple<Ts...>>>;

private:
    template<gsl::index... Is>
    class TakeOne {
    private:
        template<typename T>
        struct ValueTypeHelper;

        template<typename T>
            requires std::is_class_v<T>
        struct ValueTypeHelper<T> {
            using Type = typename T::value_type;
        };

        template<typename T>
            requires(not std::is_class_v<T>)
        struct ValueTypeHelper<T> {
            using Type = int;
        };

        template<gsl::index I>
        using ReadType = std::conditional_t<internal::IsStdArray<typename std::tuple_element_t<I, Tuple<Ts...>>::Type>{} or
                                                Concept::InstantiatedFrom<typename std::tuple_element_t<I, Tuple<Ts...>>::Type, std::vector>,
                                            ROOT::RVec<typename ValueTypeHelper<typename std::tuple_element_t<I, Tuple<Ts...>>::Type>::Type>,
                                            typename std::tuple_element_t<I, Tuple<Ts...>>::Type>;

    public:
        TakeOne(std::vector<std::unique_ptr<Tuple<Ts...>>>& data, gslx::index_sequence<Is...>);
        auto operator()(const ReadType<Is>&... value) -> void;

    private:
        std::vector<std::unique_ptr<Tuple<Ts...>>>& fData;
    };

    template<gsl::index... Is>
    TakeOne(std::vector<std::unique_ptr<Tuple<Ts...>>>, gslx::index_sequence<Is...>) -> TakeOne<Is...>;
};

} // namespace MACE::Data

#include "MACE/Data/TakeFrom.inl"
