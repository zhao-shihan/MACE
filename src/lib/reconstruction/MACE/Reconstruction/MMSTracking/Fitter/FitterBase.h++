#pragma once

#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/Hit.h++"
#include "Mustard/Data/TupleModel.h++"

#include <memory>
#include <vector>

namespace MACE::inline Reconstruction::MMSTracking::inline Fitter {

template<Mustard::Data::SuperTupleModel<Data::CDCHit> AHit, Mustard::Data::SuperTupleModel<Data::MMSTrack> ATrack>
class FitterBase {
public:
    virtual ~FitterBase() = default;

    virtual auto operator()(std::shared_ptr<const Mustard::Data::Tuple<ATrack>> seed,
                            const std::vector<std::shared_ptr<Mustard::Data::Tuple<AHit>>>& hitData) -> std::shared_ptr<Mustard::Data::Tuple<ATrack>> = 0;
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Fitter
