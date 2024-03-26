#pragma once

#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/Hit.h++"
#include "MACE/Data/TupleModel.h++"

#include <memory>
#include <vector>

namespace MACE::inline Reconstruction::MMSTracking::inline Fitter {

template<Data::TupleModelContain<Data::CDCHit> AHit, Data::TupleModelContain<Data::MMSTrack> ATrack>
class FitterBase {
public:
    virtual ~FitterBase() = default;

    virtual auto operator()(std::shared_ptr<const Data::Tuple<ATrack>> seed,
                            const std::vector<std::shared_ptr<Data::Tuple<AHit>>>& hitData) -> std::shared_ptr<Data::Tuple<ATrack>> = 0;
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Fitter
