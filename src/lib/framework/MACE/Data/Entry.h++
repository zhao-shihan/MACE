#pragma once

#include "MACE/Data/CEvalNTSTA.h++"
#include "MACE/Data/ValidModel.h++"

#include "gsl/gsl"

#include <tuple>

namespace MACE::Data {

template<ValidModel AModel>
class BasicEntry {
public:
    using Model = AModel;

public:
    template<gsl::index I>
        requires(0 <= I and I < Model::NField())
    constexpr auto Get() -> decltype(auto) { return std::get<I>(fEntry); }
    template<gsl::index I>
        requires(0 <= I and I < Model::NField())
    constexpr auto Get() const -> decltype(auto) { return std::get<I>(fEntry); }

    template<CEvalNTSTA AName>
    constexpr auto Get() -> decltype(auto) { return Get<Model::template Index<AName>()>(); }
    template<CEvalNTSTA AName>
    constexpr auto Get() const -> decltype(auto) { return Get<Model::template Index<AName>()>(); }

private:
    typename Model::FieldTuple fEntry;
};

// add specializations for customized features!
template<ValidModel AModel>
class Entry final : public BasicEntry<AModel> {};

} // namespace MACE::Data
