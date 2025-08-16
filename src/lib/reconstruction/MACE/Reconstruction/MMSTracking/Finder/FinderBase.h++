#pragma once

#include "MACE/Data/Hit.h++"
#include "MACE/Data/MMSTrack.h++"
#include "MACE/Detector/Description/CDC.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Data/TupleModel.h++"
#include "Mustard/IO/PrettyLog.h++"

#include "fmt/core.h"
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

    auto MinNHit() const -> auto { return fMinNHit; }
    auto MinNHit(int n) -> void { fMinNHit = std::max(1, n); }

protected:
    template<std::indirectly_readable AHitPointer>
        requires Mustard::Data::SuperTupleModel<typename std::iter_value_t<AHitPointer>::Model, AHit>
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
        requires Mustard::Data::SuperTupleModel<typename std::iter_value_t<AHitPointer>::Model, AHit>
    static auto GoodHitData(const std::vector<AHitPointer>& hitData) -> bool;

private:
    int fMinNHit;
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder

#include "MACE/Reconstruction/MMSTracking/Finder/FinderBase.inl"
