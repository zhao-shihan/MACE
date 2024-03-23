#pragma once

#include "MACE/Data/CDCTrack.h++"
#include "MACE/Data/Hit.h++"
#include "MACE/Data/TupleModel.h++"

#include <memory>
#include <vector>

namespace MACE::inline Reconstruction::CDCTracking::inline Finder {

template<Data::TupleModelContain<Data::CDCHit> AHit, Data::TupleModelContain<Data::CDCTrack> ATrack>
class FinderBase {
protected:
    struct Result {
        std::shared_ptr<Data::Tuple<ATrack>> seed;
        std::vector<std::vector<std::shared_ptr<Data::Tuple<AHit>>>> goodies;
        std::vector<std::shared_ptr<Data::Tuple<AHit>>> garbage;
    };

public:
    virtual ~FinderBase() = default;

    virtual auto operator()(const std::vector<std::shared_ptr<Data::Tuple<AHit>>>& hitData) -> Result = 0;
};

} // namespace MACE::inline Reconstruction::CDCTracking::inline Finder
