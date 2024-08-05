#pragma once

#include "MACE/Data/Hit.h++"
#include "MACE/Data/MMSTrack.h++"
#include "MACE/Detector/Description/CDC.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Env/Print.h++"

#include "fmt/ranges.h"

#include <iterator>
#include <memory>
#include <unordered_set>
#include <vector>

namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<Mustard::Data::SuperTupleModel<Data::CDCHit> AHit,
         Mustard::Data::SuperTupleModel<Data::MMSTrack> ATrack>
class FinderBase {
public:
    using Hit = AHit;
    using Track = ATrack;

public:
    FinderBase();
    virtual ~FinderBase() = 0;

    auto NHitThreshold() const -> auto { return fNHitThreshold; }
    auto MaxVertexRxy() const -> auto { return fMaxVertexRxy; }

    auto NHitThreshold(int n) -> void { fNHitThreshold = std::max(1, n); }
    auto MaxVertexRxy(double r) -> void { fMaxVertexRxy = std::max(0., r); }

protected:
    template<std::indirectly_readable AHitPointer>
        requires std::derived_from<std::decay_t<std::iter_value_t<AHitPointer>>, Mustard::Data::Tuple<AHit>>
    struct Result {
        struct GoodTrack {
            std::vector<AHitPointer> hitData;
            std::shared_ptr<Mustard::Data::Tuple<ATrack>> seed;
        };
        std::unordered_map<int, GoodTrack> good;
        std::vector<AHitPointer> garbage;
    };

protected:
    template<std::indirectly_readable AHitPointer>
        requires std::derived_from<std::decay_t<std::iter_value_t<AHitPointer>>, Mustard::Data::Tuple<AHit>>
    static auto GoodHitData(const std::vector<AHitPointer>& hitData) -> bool;

protected:
    int fNHitThreshold;
    double fMaxVertexRxy;
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder

#include "MACE/Reconstruction/MMSTracking/Finder/FinderBase.inl"
