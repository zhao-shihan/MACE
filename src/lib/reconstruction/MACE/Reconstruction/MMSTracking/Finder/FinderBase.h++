#pragma once

#include "MACE/Data/Hit.h++"
#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Env/Print.h++"

#include "fmt/ranges.h"

#include <iterator>
#include <memory>
#include <unordered_set>
#include <vector>

namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<Data::SuperTupleModel<Data::CDCHit> AHit,
         Data::SuperTupleModel<Data::MMSTrack> ATrack>
class FinderBase {
public:
    using Hit = AHit;
    using Track = ATrack;

public:
    virtual ~FinderBase() = 0;

protected:
    template<std::indirectly_readable AHitPointer>
        requires std::derived_from<std::decay_t<std::iter_value_t<AHitPointer>>, Data::Tuple<AHit>>
    struct Result {
        struct GoodTrack {
            std::vector<AHitPointer> hitData;
            std::shared_ptr<Data::Tuple<ATrack>> seed;
        };
        auto NGoodTrack() const -> auto { return ssize(good); }
        std::unordered_map<int, GoodTrack> good;
        std::vector<AHitPointer> garbage;
    };

protected:
    template<std::indirectly_readable AHitPointer>
        requires std::derived_from<std::decay_t<std::iter_value_t<AHitPointer>>, Data::Tuple<AHit>>
    static auto GoodHitData(const std::vector<AHitPointer>& hitData) -> bool;
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder

#include "MACE/Reconstruction/MMSTracking/Finder/FinderBase.inl"
