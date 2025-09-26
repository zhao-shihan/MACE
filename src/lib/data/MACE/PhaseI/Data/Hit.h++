#pragma once

#include "MACE/PhaseI/Data/RawHit.h++"

#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

namespace MACE::PhaseI::Data {

namespace internal {

using HitEventIDHitID = Mustard::Data::TupleModel<
    Mustard::Data::Value<int, "EvtID", "Event ID">,
    Mustard::Data::Value<int, "HitID", "Hit ID">>;

} // namespace internal

using SciFiHit = Mustard::Data::TupleModel<
    internal::HitEventIDHitID,
    SciFiRawHit>;

using MRPCHit = Mustard::Data::TupleModel<
    internal::HitEventIDHitID,
    MRPCRawHit>;
    
} // namespace MACE::PhaseI::Data
