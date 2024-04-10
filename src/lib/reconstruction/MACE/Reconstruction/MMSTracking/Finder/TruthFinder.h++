#pragma once

#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Env/Print.h++"
#include "MACE/External/gfx/timsort.hpp"
#include "MACE/Reconstruction/MMSTracking/Finder/FinderBase.h++"

#include <algorithm>
#include <iterator>
#include <ranges>
#include <unordered_set>

namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<Data::SuperTupleModel<Data::CDCHit> AHit = Data::CDCSimHit,
         Data::SuperTupleModel<Data::MMSTrack> ATrack = Data::MMSSimTrack>
class TruthFinder : public FinderBase<AHit, ATrack> {
protected:
    using Base = FinderBase<AHit, ATrack>;

public:
    TruthFinder();
    virtual ~TruthFinder() override = default;

    auto NHitThreshold() const -> auto { return fNHitThreshold; }
    auto NHitThreshold(int n) -> void { fNHitThreshold = std::max(1, n); }

    template<std::indirectly_readable AHitPointer>
        requires std::derived_from<std::decay_t<std::iter_value_t<AHitPointer>>, Data::Tuple<AHit>>
    auto operator()(const std::vector<AHitPointer>& hitData, int = {}) -> Base::template Result<AHitPointer>;

protected:
    int fNHitThreshold;
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder

#include "MACE/Reconstruction/MMSTracking/Finder/TruthFinder.inl"
