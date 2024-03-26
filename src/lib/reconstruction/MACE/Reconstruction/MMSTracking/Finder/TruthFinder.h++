#pragma once

#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/Hit.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Env/Print.h++"
#include "MACE/External/gfx/timsort.hpp"
#include "MACE/Reconstruction/MMSTracking/Finder/FinderBase.h++"

#include <algorithm>
#include <iterator>

namespace MACE::inline Reconstruction::MMSTracking::inline Finder {

template<Data::TupleModelContain<Data::CDCSimHit> AHit, Data::TupleModelContain<Data::MMSSimTrack> ATrack>
class TruthFinder : public FinderBase<AHit, ATrack> {
protected:
    using Base = FinderBase<AHit, ATrack>;
    using HitCollection = Base::HitCollection;
    using Result = Base::Result;

public:
    TruthFinder();
    virtual ~TruthFinder() override = default;

    auto operator()(const HitCollection& hitData, int = {}) -> Result;

protected:
    int fNHitThreshold;
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Finder

#include "MACE/Reconstruction/MMSTracking/Finder/TruthFinder.inl"
