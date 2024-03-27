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

namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<std::indirectly_readable AHit = std::shared_ptr<Data::Tuple<Data::CDCSimHit>>,
         Data::TupleContain<Data::Tuple<Data::MMSSimTrack>> ATrack = Data::Tuple<Data::MMSSimTrack>>
    requires Data::TupleContain<std::iter_value_t<AHit>, Data::Tuple<Data::CDCSimHit>>
class TruthFinder : public FinderBase<AHit, ATrack> {
protected:
    using Base = FinderBase<AHit, ATrack>;
    using Result = Base::Result;

public:
    TruthFinder();
    virtual ~TruthFinder() override = default;

    auto NHitThreshold() const -> auto { return fNHitThreshold; }
    auto NHitThreshold(int n) -> void { fNHitThreshold = std::max(1, n); }

    auto operator()(const std::vector<AHit>& hitData, int = {}) -> Result;

protected:
    int fNHitThreshold;
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder

#include "MACE/Reconstruction/MMSTracking/Finder/TruthFinder.inl"
