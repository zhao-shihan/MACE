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

protected:
    template<std::indirectly_readable AHitPointer>
        requires Mustard::Data::SuperTupleModel<typename std::iter_value_t<AHitPointer>::Model, AHit>
    struct Result {
        std::shared_ptr<Mustard::Data::Tuple<ATrack>> track;
        std::vector<AHitPointer> fitted;
        std::vector<AHitPointer> failed;
    };
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Fitter
