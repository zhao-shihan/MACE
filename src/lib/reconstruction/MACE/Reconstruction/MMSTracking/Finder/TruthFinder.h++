#pragma once

#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/SimHit.h++"
#include "Mustard/Data/Tuple.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "Mustard/Env/Print.h++"
#include "MACE/Reconstruction/MMSTracking/Finder/FinderBase.h++"

#include "gfx/timsort.hpp"

#include <algorithm>
#include <iterator>
#include <ranges>
#include <unordered_set>

namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<Mustard::Data::SuperTupleModel<Data::CDCHit> AHit = Data::CDCSimHit,
         Mustard::Data::SuperTupleModel<Data::MMSTrack> ATrack = Data::MMSSimTrack>
class TruthFinder : public FinderBase<AHit, ATrack> {
protected:
    using Base = FinderBase<AHit, ATrack>;

public:
    TruthFinder();
    virtual ~TruthFinder() override = default;

    auto NHitThreshold() const -> auto { return fNHitThreshold; }
    auto NHitThreshold(int n) -> void { fNHitThreshold = std::max(1, n); }

    template<std::indirectly_readable AHitPointer>
        requires std::derived_from<std::decay_t<std::iter_value_t<AHitPointer>>, Mustard::Data::Tuple<AHit>>
    auto operator()(const std::vector<AHitPointer>& hitData, int = {}) -> Base::template Result<AHitPointer>;

protected:
    int fNHitThreshold;
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder

#include "MACE/Reconstruction/MMSTracking/Finder/TruthFinder.inl"
