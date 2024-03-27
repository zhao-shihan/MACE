#pragma once

#include "MACE/Data/Hit.h++"
#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Env/Print.h++"

#include "fmt/ranges.h"

#include <iterator>
#include <memory>
#include <unordered_set>
#include <vector>

namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<std::indirectly_readable AHit,
         Data::TupleContain<Data::Tuple<Data::MMSTrack>> ATrack>
    requires Data::TupleContain<std::iter_value_t<AHit>, Data::Tuple<Data::CDCHit>>
class FinderBase {
public:
    using Hit = AHit;
    using Track = ATrack;

public:
    virtual ~FinderBase() = 0;

protected:
    struct Result {
        struct GoodTrack {
            std::vector<AHit> hitData;
            std::shared_ptr<ATrack> seed;
        };
        auto NGoodTrack() const -> auto { return ssize(good); }
        std::unordered_map<int, GoodTrack> good;
        std::vector<AHit> garbage;
    };

protected:
    static auto GoodHitData(const std::vector<AHit>& hitData) -> bool;
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder

#include "MACE/Reconstruction/MMSTracking/Finder/FinderBase.inl"
