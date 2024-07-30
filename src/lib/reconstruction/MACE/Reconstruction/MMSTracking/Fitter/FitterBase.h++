#pragma once

#include "MACE/Data/Hit.h++"
#include "MACE/Data/MMSTrack.h++"

#include "Mustard/Data/TupleModel.h++"

#include <memory>
#include <vector>

namespace MACE::inline Reconstruction::MMSTracking::inline Fitter {

template<Mustard::Data::SuperTupleModel<Data::CDCHit> AHit,
         Mustard::Data::SuperTupleModel<Data::MMSTrack> ATrack>
class FitterBase {
public:
    using Hit = AHit;
    using Track = ATrack;

public:
    virtual ~FitterBase() = default;
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Fitter
