#pragma once

#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/Hit.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Env/Print.h++"

#include "fmt/ranges.h"

#include <memory>
#include <unordered_map>
#include <vector>

namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<Data::TupleModelContain<Data::CDCHit> AHit, Data::TupleModelContain<Data::MMSTrack> ATrack>
class FinderBase {
public:
    using HitModel = AHit;
    using TrackModel = ATrack;

protected:
    using HitCollection = std::vector<std::shared_ptr<Data::Tuple<AHit>>>;

    struct Result {
        auto NGoodTrack() const -> auto { return ssize(seed); }
        std::unordered_map<int, std::shared_ptr<Data::Tuple<ATrack>>> seed;
        std::unordered_map<int, HitCollection> goodies;
        HitCollection garbage;
    };

protected:
    static auto GoodHitData(const HitCollection& hitData) -> bool;
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder

#include "MACE/Reconstruction/MMSTracking/Finder/FinderBase.inl"
